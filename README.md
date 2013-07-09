##Fled

A program used to demonstrate finding the morse code letter that a blinking light is emitting

####Usage

fled &lt;duration&rt; &lt;resolution x&rt; &lt;resolution y&rt; &lt;patch_height&rt; &lt;patch_width&rt; &lt;channel&rt;

&lt;duration&rt;
	how long the camera will record the light
	
&lt;resolution x&rt;
	resizes the images to the number of pixels in the x direction
	setting this value to -1 will make the program use the original size
	
&lt;resolution x&rt;
	see &lt;resolution y&rt;
	
&lt;patch_height&rt;
	the height of the convolution kernel in pixels
	
&lt;patch_width&rt;
	the width of the convolution kernel in pixels
	
&lt;channel&rt;
	the channel to be analysed, can be one of
		* H &mdash; Hue channel of the HLS color space
		* L &mdash; Light channel of the HLS color space
		* S &mdash; Saturation channel of the HLS color space
		* B &mdash; Blue channel of the BGR color space
		* G &mdash; Green channel of the BGR color space
		* R &mdash; Red channel of the BGR color space
		* GREY &mdash; A greyscale version of the image
		
if a value is input that is not included in the list above the program will default
to a greyscale image.