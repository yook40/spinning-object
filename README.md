Object rotation

rotation matrices are obtained by trig identity (the angle in one matrix and those in the other two are independent):

	/* about y-axis:

     cos(phi)     0    sin(phi)
     
        0         1       0
        
    -sin(phi)     0    cos(phi)

  */

  /* about x-axis:

        1         0           0

        0      cos(phi)    sin(phi)

        0     -sin(phi)    cos(phi)

  */

  /* about z-axis:

        cos(phi)  sin(phi)    0

       -sin(phi)  cos(phi)    0

           0         0        1

  */


