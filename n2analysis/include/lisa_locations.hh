/* ***** Updated LISA locations  ***** 
 * ***** according to the survey ***** 
 * ***** conducted on 30 October ***** 
 * ***** 2017 by Dave Sanderson. ***** */

//LISA 1 = J,K,L,M (second table)
//LISA 2 = N,O,P,Q,R (front table)

// LISA 1 indv bar x positions (ARRAY FRAME)

for(int i=9;i<13;i++)
  {
  for(int j=0;j<16;j++)
    { location.x[i][j] = 0.0; }
  }

// LISA 2 indv bar x positions (ARRAY FRAME)
for(int i=13;i<18;i++)
  {
  for(int j=0;j<16;j++)
    {location.x[i][j] = 0.0; }
  }


// THR 12 Dec 2017: force neutron x distributions to 0
// for coincidences with F-27
#include "lisaMeans.out"

// LISA 2 indv bar y positions (ARRAY FRAME)
for(int i=13;i<18;i++)
{
location.y[i][0] = -81.558;
location.y[i][1] = -71.158;
location.y[i][2] = -60.758;
location.y[i][3] = -50.358;
location.y[i][4] = -39.958;
location.y[i][5] = -28.558;
location.y[i][6] = -19.158;
location.y[i][7] = -8.758;
location.y[i][8] = 1.642;
location.y[i][9] = 12.042;
location.y[i][10] = 22.442;
location.y[i][11] = 32.842;
location.y[i][12] = 43.242;
location.y[i][13] = 53.642;
location.y[i][14] = 64.042;
location.y[i][15] = 74.442;
}


// LISA 2 wall z positions (ARRAY FRAME)
for(int j=0;j<16;j++) {
  location.z[13][j] = 0.;
  location.z[14][j] = 10.4;
  location.z[15][j] = 20.8;
  // 40.0 cm gap
  location.z[16][j] = 71.2;
  location.z[17][j] = 81.6;
}



//Lisa 1 indv bar y positions (ARRAY FRAME)

for(int i=9;i<13;i++){
location.y[i][0] = -82.242;
location.y[i][1] = -71.842;
location.y[i][2] = -61.442;
location.y[i][3] = -51.042;
location.y[i][4] = -40.642;
location.y[i][5] = -30.242;
location.y[i][6] = -19.842;
location.y[i][7] = -9.442;
location.y[i][8] = 0.958;
location.y[i][9] = 11.358;
location.y[i][10] = 21.758;
location.y[i][11] = 32.158;
location.y[i][12] = 42.558;
location.y[i][13] = 52.958;
location.y[i][14] = 63.358;
location.y[i][15] = 73.758;
}


/* add shift to y
for(int i=9;i<18;i++)
{
	for(int j=0;j<16;j++)
	{
		location.y[i][j] += 8.84;
	}

}
*/

// LISA 1 z (ARRAY FRAME)
for(int j=0;j<16;j++) {
	location.z[9][j]  = 0.;
	location.z[10][j] = 10.4;
	// 50.5 cm gap
	location.z[11][j] = 71.3;
	location.z[12][j] = 81.7;

}

// (LAB FRAME)
location.LISA1origin_x=-0.456;
location.LISA1origin_y=0.4936;
location.LISA1origin_z=812.2309;

location.LISA2origin_x=-1.408;
location.LISA2origin_y=1.1907;
location.LISA2origin_z=595.7084;

/* Define inverse matrices for transforming between
 * coordinates
 * First index is row, second is column
 * For e15118, all arrays lie on the z-axis
 * so their array frames coincide with the lab
 * frame
 *
 * ----- UPDATED 8 November 2017 THR -----
 *
 * The survey gives the normal vector (in the lab
 * frame) to the front
 * walls of each table
*/


// LISA 1 inverse matrix
location.Jinv_LISA1[0][0]=1.;
location.Jinv_LISA1[1][0]=0.;
location.Jinv_LISA1[2][0]=0.;
location.Jinv_LISA1[0][1]=0.;
location.Jinv_LISA1[1][1]=1.;
location.Jinv_LISA1[2][1]=0.;
location.Jinv_LISA1[0][2]=0.;
location.Jinv_LISA1[1][2]=0.;
location.Jinv_LISA1[2][2]=1.;

// LISA 2 inverse matrix
location.Jinv_LISA2[0][0]=1.;
location.Jinv_LISA2[1][0]=0.;
location.Jinv_LISA2[2][0]=0.;
location.Jinv_LISA2[0][1]=0.;
location.Jinv_LISA2[1][1]=1.;
location.Jinv_LISA2[2][1]=0.;
location.Jinv_LISA2[0][2]=0.;
location.Jinv_LISA2[1][2]=0.;
location.Jinv_LISA2[2][2]=1.;


