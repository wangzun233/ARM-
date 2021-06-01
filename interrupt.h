#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__


#define GICD_CTRL        (*((volatile unsigned int *)0xC0009000))
#define GICD_TYPER       (*((volatile unsigned int *)0xC0009004))
#define GICD_IIDR        (*((volatile unsigned int *)0xC0009008))

#define GICD_IGROUPR0    (*((volatile unsigned int *)0xC0009080))
#define GICD_IGROUPR1    (*((volatile unsigned int *)0xC0009084))
#define GICD_IGROUPR2    (*((volatile unsigned int *)0xC0009088))
#define GICD_IGROUPR3    (*((volatile unsigned int *)0xC000908C))
#define GICD_IGROUPR4    (*((volatile unsigned int *)0xC0009090))

#define GICD_ISENABLER0  (*((volatile unsigned int *)0xC0009100))
#define GICD_ISENABLER1  (*((volatile unsigned int *)0xC0009104))
#define GICD_ISENABLER2  (*((volatile unsigned int *)0xC0009108))
#define GICD_ISENABLER3  (*((volatile unsigned int *)0xC000910C))
#define GICD_ISENABLER4  (*((volatile unsigned int *)0xC0009110))

#define GICD_ISCENABLER0  (*((volatile unsigned int *)0xC0009180))
#define GICD_ISCENABLER1  (*((volatile unsigned int *)0xC0009184))
#define GICD_ISCENABLER2  (*((volatile unsigned int *)0xC0009188))
#define GICD_ISCENABLER3  (*((volatile unsigned int *)0xC000918C))
#define GICD_ISCENABLER4  (*((volatile unsigned int *)0xC0009190))


#define GICD_ISPENDR0  (*((volatile unsigned int *)0xC0009200))
#define GICD_ISPENDR1  (*((volatile unsigned int *)0xC0009204))
#define GICD_ISPENDR2  (*((volatile unsigned int *)0xC0009208))
#define GICD_ISPENDR3  (*((volatile unsigned int *)0xC000920C))
#define GICD_ISPENDR4  (*((volatile unsigned int *)0xC0009210))

#define GICD_ICPENDERR0  (*((volatile unsigned int *)0xC0009280))
#define GICD_ICPENDERR1  (*((volatile unsigned int *)0xC0009284))
#define GICD_ICPENDERR2  (*((volatile unsigned int *)0xC0009288))
#define GICD_ICPENDERR3  (*((volatile unsigned int *)0xC000928C))
#define GICD_ICPENDERR4  (*((volatile unsigned int *)0xC0009290))

#define GICD_ISACTIVER0  (*((volatile unsigned int *)0xC0009300))
#define GICD_ISACTIVER1  (*((volatile unsigned int *)0xC0009304))
#define GICD_ISACTIVER2  (*((volatile unsigned int *)0xC0009308))
#define GICD_ISACTIVER3  (*((volatile unsigned int *)0xC000930C))
#define GICD_ISACTIVER4  (*((volatile unsigned int *)0xC0009310))


#define GICD_ISCCTIVER0  (*((volatile unsigned int *)0xC0009380))
#define GICD_ISCCTIVER1  (*((volatile unsigned int *)0xC0009384))
#define GICD_ISCCTIVER2  (*((volatile unsigned int *)0xC0009388))
#define GICD_ISCCTIVER3  (*((volatile unsigned int *)0xC000938C))
#define GICD_ISCCTIVER4  (*((volatile unsigned int *)0xC0009390))

#define GICD_IPRIORITYR      (0xC0009400)
#define GICD_ITARGETSR       (0xC0009800)

#define GICD_ICFGR0          (*((volatile unsigned int *)0xC0009C00))
#define GICD_ICFGR1          (*((volatile unsigned int *)0xC0009C04))
#define GICD_ICFGR2          (*((volatile unsigned int *)0xC0009C08))
#define GICD_ICFGR3          (*((volatile unsigned int *)0xC0009C0C))
#define GICD_ICFGR4          (*((volatile unsigned int *)0xC0009C10))
#define GICD_ICFGR5          (*((volatile unsigned int *)0xC0009C14))
#define GICD_ICFGR6          (*((volatile unsigned int *)0xC0009C18))
#define GICD_ICFGR7          (*((volatile unsigned int *)0xC0009C1C))
#define GICD_ICFGR8          (*((volatile unsigned int *)0xC0009C20))
#define GICD_ICFGR9          (*((volatile unsigned int *)0xC0009C24))

#define GICD_PPISR           (*((volatile unsigned int *)0xC0009D00))

#define GICD_SPISR0          (*((volatile unsigned int *)0xC0009D04))
#define GICD_SPISR1          (*((volatile unsigned int *)0xC0009D08))
#define GICD_SPISR2          (*((volatile unsigned int *)0xC0009D0C))
#define GICD_SPISR3          (*((volatile unsigned int *)0xC0009D10))

#define GICD_SGIR            (*((volatile unsigned int *)0xC0009F00))

#define GICC_CTRL            (*((volatile unsigned int *)0xC000A000))
#define GICC_PMR             (*((volatile unsigned int *)0xC000A004))
#define GICC_BPR             (*((volatile unsigned int *)0xC000A008))
#define GICC_IAR             (*((volatile unsigned int *)0xC000A00C))
#define GICC_EOIR            (*((volatile unsigned int *)0xC000A010))
#define GICC_RPR             (*((volatile unsigned int *)0xC000A014))
#define GICC_HPPIR           (*((volatile unsigned int *)0xC000A018))
#define GICC_ABPR            (*((volatile unsigned int *)0xC000A01C))
#define GICC_AIAR            (*((volatile unsigned int *)0xC000A020))
#define GICC_AEOIR           (*((volatile unsigned int *)0xC000A024))
#define GICC_AHIPPIR         (*((volatile unsigned int *)0xC000A028))


#define GICC_APR0     (*((volatile unsigned int *)0xC000A0D0))
#define GICC_NSAPR0   (*((volatile unsigned int *)0xC000A0E0))

#define GICC_DIR      (*((volatile unsigned int *)0xC000B000))

extern int interrupt_init (void);

#endif //__INTERRUPT_H__

