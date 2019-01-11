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
    float a = newcol[3];

    float c = 2.0;
    r = r * c + 0.5;
    g = g * c + 0.5;
    b = b * c + 0.5;

    newcol = vec4(r,g,b,a);

    gl_FragColor = newcol;
}
//! [0]

