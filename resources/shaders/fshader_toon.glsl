#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;

//! [0]
void main()
{
    // Set fragment color from texture
    //gl_FragColor = texture2D(texture, v_texcoord);

    vec4 newcol = texture2D(texture, v_texcoord);

    float r = newcol[0];
    float g = newcol[1];
    float b = newcol[2];
    float a = newcol[3] > 0.5 ? 1.0 : 0.0;

    //if((r + g + b) < 0.6) discard; // degage l'ombre

    // ombre archer 271b11 (0,152941176, 0,10590, 0,066666667)
    // ombre knight 080c00 (0,031372549, 0,047058824, 0.)

    float epsilon = 0.001;
    if(abs(r - 0.152941176) < epsilon && abs(g - 0.10590) < epsilon && abs(b - 0.066666667) < epsilon) discard;
    if(abs(r - 0.031372549) < epsilon && abs(g - 0.047058824) < epsilon && abs(b - 0.00000) < epsilon) discard;



    /*r = r  * 3.;
    if(r > 1.) r = 1.;
    g = g / 4.;
    b = b * 4.;*/



    float f = 2.0;
    float f2 = 0.25;

    r = float(int(r * f)) / f + f2;
    g = float(int(g * f)) / f + f2;
    b = float(int(b * f)) / f + f2;

    newcol = vec4(r,g,b,a);

    gl_FragColor = newcol;
}
//! [0]

