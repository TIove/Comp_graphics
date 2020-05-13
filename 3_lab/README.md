# Dithering images
```
Arguments in through the command line:
lab#.exe <name_of_input_file> <name_of_output_file> <gradient> <dithering> <bitRate> <Gamma> 
Where <option> is:
<gradient>: 0 - using input image, 1 - draw horizontal gradient (0-255)
<dithering> - Algorithm of dither:
0 – None;
1 – Ordered (8x8);
2 – Random;
3 – Floyd–Steinberg;
4 – Jarvis, Judice, Ninke;
5 - Sierra (Sierra-3);
6 - Atkinson;
7 - Halftone (4x4, orthogonal);
<bitRate> - bitRate of dith result (1..8);
<gamma>: 0 - sRGB gamma, otherwise - common gamma with set value.
```
 ### Default
![Default](images/default.png)
# Changed images
  ### None
  ![None](images/0.png)  
  ### Ordered (8x8)
  ![Ordered](images/1.png)  
  ### Random
  ![Random](images/2.png)  
  ### Floyd–Steinberg
  ![FS](images/3.png)  
  ### Jarvis, Judice, Ninke
  ![JJN](images/4.png)  
  ### Sierra (Sierra-3)
  ![Sierra](images/5.png)  
  ### Atkinson
  ![Atkinson](images/6.png)  
  ### Halftone (4x4, orthogonal)
  ![Halftone](images/7.png)  
