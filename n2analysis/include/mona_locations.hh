/* ***** Updated LISA locations  ***** 
 * ***** according to the survey ***** 
 * ***** conducted on 30 October ***** 
 * ***** 2017 by Dave Sanderson. ***** */

//Mona indv bar x positions (ARRAY FRAME)
 for (int i=0;i<9;i++) {
   for(int j=0;j<16;j++) {
      location.x[i][j] = 0.0;
   }
}

//Mona Y positions (ARRAY FRAME)

for (int i=0;i<9;i++){
 location.y[i][0]  = -75.;
 location.y[i][1]  = -65.;
 location.y[i][2]  = -55.;
 location.y[i][3]  = -45.;
 location.y[i][4]  = -35.;
 location.y[i][5]  = -25.;
 location.y[i][6]  = -15.;
 location.y[i][7]  = -5.;
 location.y[i][8]  = 5.;
 location.y[i][9]  = 15.;
 location.y[i][10] = 25.;
 location.y[i][11] = 35.;
 location.y[i][12] = 45.;
 location.y[i][13] = 55.;
 location.y[i][14] = 65.;
 location.y[i][15] = 75.;
 }

//Mona Z positions (ARRAY FRAME)

for(int j=0;j<16;j++) {
	location.z[0][j] = 0.;
	location.z[1][j] = 10.;
	location.z[2][j] = 20.;
	// 28.0 cm gap
	location.z[3][j] = 58.;
	location.z[4][j] = 68.;
	// 24.0 cm gap
	location.z[5][j] = 102.;
	location.z[6][j] = 112.;
	location.z[7][j] = 122.;
	location.z[8][j] = 2253000.;//approximate distance to LANL

}

// (LAB FRAME)
location.MONAorigin_x=-2.374;
location.MONAorigin_y=-2.314;
location.MONAorigin_z=1040.768;

/* Define inverse matrices for transforming between
 * coordinates
 * First index is row, second is column
 * For e15118, all arrays lie on the z-axis
 * so their array frames coincide with the lab
 * frame
 * THR 12/20/2016
*/

// MoNA inverse matrix
location.Jinv_MONA[0][0]=1.;
location.Jinv_MONA[1][0]=0.;
location.Jinv_MONA[2][0]=0.;
location.Jinv_MONA[0][1]=0.;
location.Jinv_MONA[1][1]=1.;
location.Jinv_MONA[2][1]=0.;
location.Jinv_MONA[0][2]=0.;
location.Jinv_MONA[1][2]=0.;
location.Jinv_MONA[2][2]=1.;

