#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "units_user.h"
#include <string.h>

int oom_unit(int argc, char *argv[], int fd)
{
    void *p;
    int total = 0;
    while(1)
    {
        p = malloc(1024*1024);
        if (p == NULL)
        {
            printf("malloc failed\n");
            break;
        }
        memset(p, 0x0, 1024*1024);
        printf("total malloc = %u byte\n", total += 1024*1024);
        usleep(1000*100);
    }
}

/*
[   98.066887] kprobelabs invoked oom-killer: gfp_mask=0x1100cca(GFP_HIGHUSER_MOVABLE), order=0, oom_score_adj=0                                      
[   98.066939] CPU: 0 PID: 726 Comm: kprobelabs Tainted: G           O      5.10.160 #23                                                              
[   98.066953] Hardware name: Rockchip (Device Tree)                                                                                                  
[   98.067011] [<b000f56d>] (unwind_backtrace) from [<b000e03f>] (show_stack+0xb/0xc)                                                                 
[   98.067046] [<b000e03f>] (show_stack) from [<b03b4087>] (dump_header+0x37/0x148)                                                                   
[   98.067083] [<b03b4087>] (dump_header) from [<b004f059>] (oom_kill_process+0x3d/0x178)                                                             
[   98.067115] [<b004f059>] (oom_kill_process) from [<b004f5eb>] (out_of_memory+0x21f/0x264)                                                          
[   98.067148] [<b004f5eb>] (out_of_memory) from [<b006b287>] (__alloc_pages_nodemask+0x451/0x506)
[   98.067182] [<b006b287>] (__alloc_pages_nodemask) from [<b004dbc7>] (pagecache_get_page.part.12+0x8b/0xd4)
[   98.067212] [<b004dbc7>] (pagecache_get_page.part.12) from [<b004e417>] (filemap_fault+0x201/0x35a)
[   98.067242] [<b004e417>] (filemap_fault) from [<b005f5b1>] (__do_fault+0x29/0x40)
[   98.067271] [<b005f5b1>] (__do_fault) from [<b006119d>] (handle_mm_fault+0x241/0x450)
[   98.067300] [<b006119d>] (handle_mm_fault) from [<b000fb1f>] (do_page_fault+0x10f/0x188)
[   98.067328] [<b000fb1f>] (do_page_fault) from [<b000fcf1>] (do_PrefetchAbort+0x25/0x58)
[   98.067358] [<b000fcf1>] (do_PrefetchAbort) from [<b00092af>] (__pabt_usr+0x4f/0x50)
[   98.067375] Exception stack(0xb14a9fb0 to 0xb14a9ff8)
[   98.067396] 9fa0:                                     a5cf0008 00000000 00100000 a5d18ff8
[   98.067418] 9fc0: 000d7000 00000000 00000000 00000000 00000000 00000000 a6fa7f70 aebc4c44
[   98.067439] 9fe0: 00021030 aebc4c18 00010aec a6f3bb14 20000030 ffffffff
[   98.067452] Mem-Info:
[   98.067488] active_anon:47 inactive_anon:4907 isolated_anon:0
[   98.067488]  active_file:0 inactive_file:0 isolated_file:0
[   98.067488]  unevictable:0 dirty:0 writeback:0
[   98.067488]  slab_reclaimable:765 slab_unreclaimable:1133
[   98.067488]  mapped:0 shmem:80 pagetables:56 bounce:0
[   98.067488]  free:183 free_pcp:5 free_cma:0
[   98.067524] Node 0 active_anon:188kB inactive_anon:19628kB active_file:0kB inactive_file:0kB unevictable:0kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:0kB writeback:0kB shmem:320kB writeback_tmp:0kB kernel_stack:584kB all_unreclaimable? yes
[   98.067568] Normal free:732kB min:732kB low:912kB high:1092kB reserved_highatomic:0KB active_anon:188kB inactive_anon:19628kB active_file:0kB inactive_file:0kB unevictable:0kB writepending:0kB present:65536kB managed:33820kB mlocked:0kB pagetables:224kB bounce:0kB free_pcp:20kB local_pcp:20kB free_cma:0kB
[   98.067581] lowmem_reserve[]: 0 0
[   98.067609] Normal: 25*4kB (UME) 9*8kB (UE) 13*16kB (UE) 1*32kB (U) 1*64kB (M) 2*128kB (M) 0*256kB 0*512kB 0*1024kB = 732kB
[   98.067695] 80 total pagecache pages
[   98.067710] 0 pages in swap cache
[   98.067723] Swap cache stats: add 0, delete 0, find 0/0
[   98.067735] Free swap  = 0kB
[   98.067745] Total swap = 0kB
[   98.067755] 16384 pages RAM
[   98.067765] 0 pages HighMem/MovableOnly
[   98.067776] 7929 pages reserved
[   98.067787] 6144 pages cma reserved
[   98.067799] Tasks state (memory values in pages):
[   98.067812] [  pid  ]   uid  tgid total_vm      rss pgtables_bytes swapents oom_score_adj name
[   98.067844] [     72]     0    72      398       15     6144        0             0 syslogd
[   98.067866] [     76]     0    76      397       14     6144        0             0 klogd
[   98.067887] [     87]     0    87      405      109     6144        0         -1000 udevd
[   98.067910] [    226]     0   226     1616      112    12288        0             0 ntpd
[   98.067936] [    280]     0   280     1241       80    10240        0         -1000 sshd
[   98.067957] [    286]     0   286      398       15     6144        0             0 telnetd
[   98.067978] [    348]     0   348     3595       32    18432        0             0 adbd
[   98.068000] [    637]     0   637      402       20     6144        0             0 S99usb0config
[   98.068020] [    638]     0   638      399       17     6144        0             0 getty
[   98.068042] [    653]     0   653      403       21     6144        0             0 sh
[   98.068063] [    726]     0   726     4816     4424    24576        0             0 kprobelabs
[   98.068081] oom-kill:constraint=CONSTRAINT_NONE,nodemask=(null),task=kprobelabs,pid=726,uid=0
[   98.068131] Out of memory: Killed process 726 (kprobelabs) total-vm:19264kB, anon-rss:17696kB, file-rss:0kB, shmem-rss:0kB, UID:0 pgtables:24kB oom
_score_adj:0
[   98.079338] oom_reaper: reaped process 726 (kprobelabs), now anon-rss:0kB, file-rss:0kB, shmem-rss:0kB
[root@luckfox root]# 
*/