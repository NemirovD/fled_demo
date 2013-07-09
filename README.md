##Fled

A program used to demonstrate finding the morse code letter that a blinking light is emitting

####Usage

fled &lt;duration&gt; &lt;resolution x&gt; &lt;resolution y&gt; &lt;patch_height&gt; &lt;patch_width&gt; &lt;channel&gt;

&lt;duration&gt;
	how long the camera will record the light
	
&lt;resolution x&gt;
	resizes the images to the number of pixels in the x direction
	setting this value to -1 will make the program use the original size
	
&lt;resolution x&gt;
	see &lt;resolution y&gt;
	
&lt;patch_height&gt;
	the height of the convolution kernel in pixels
	
&lt;patch_width&gt;
	the width of the convolution kernel in pixels
	
&lt;channel&gt;
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