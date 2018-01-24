/* This file is where calibration parameters for the Si
 * detectors of the segmented target (st) are found.
 *
 * There are 3 sets of slopes and offset variables:
 *   (1) corner gainmatching (sl,off) x16
 *   (2) x,y position calculation (sl,off) x 4
 *   (3) energy calibration (sl,off) x4
*/

#ifndef __HAVE_ST_VARIABLES
#define __HAVE_ST_VARIABLES

// initialize
for(int i=0; i<4; i++)
{
  for(int j=0; j<4; j++)
  {
    st.cnr_slope[i][j] = 1.0;
    st.cnr_offset[i][j]= 0.0;
  }

  st.x_slope[i] = 1.0;
  st.x_offset[i]= 0.0;

  st.y_slope[i] = 1.0;
  st.y_offset[i]= 0.0;

  st.e_slope[i] = 1.0;
  st.e_offset[i]= 0.0;
}

// include files with calibration parameters here or put them here directly
/* JAF online calibration July 2016
st.e_slope[0]=0.0097829781;
st.e_slope[1]=0.0096702505;
st.e_slope[2]=0.0107002770;
st.e_slope[3]=0.0107636954;

st.e_offset[0]=0.2651851345;
st.e_offset[1]=0.7831875147;
st.e_offset[2]=1.1581624157;
st.e_offset[3]=0.0489592907;
*/
/* THR offline calibration based on run 1051 */
st.e_slope[0] = 0.00994644;
st.e_slope[1] = 0.00951454;
st.e_slope[2] = 0.0108086;
st.e_slope[3] = 0.00946289;

st.e_offset[0] = 0.0793953;
st.e_offset[1] = 0.708855;
st.e_offset[2] = 0.761865;
st.e_offset[3] = 1.71199;



#endif
