uniform sampler2D texture;

uniform vec4 flash_color;

void main()
{


	vec4 pixel_color = texture2D(texture, gl_TexCoord[0].xy);
	float percent = flash_color.a;

	vec4 colorDifference = vec4(0,0,0,1);

	colorDifference.r = flash_color.r - pixel_color.r;
	colorDifference.g = flash_color.g - pixel_color.g;
	colorDifference.b = flash_color.b - pixel_color.b;
	pixel_color.r = pixel_color.r + colorDifference.r * percent;
	pixel_color.g = pixel_color.g +colorDifference.g * percent;
	pixel_color.b =pixel_color.b + colorDifference.b * percent;


	gl_FragColor = pixel_color; 

}