/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature REDSIG = vex::vision::signature (1, 5059, 7141, 6100, -929, 121, -404, 3.2, 0);
vex::vision::signature BLUESIG = vex::vision::signature (2, -2761, -1973, -2368, 8387, 9877, 9132, 8.6, 0);
vex::vision::signature GREENSIG = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision1 = vex::vision (vex::PORT9, 101, REDSIG, BLUESIG, GREENSIG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/