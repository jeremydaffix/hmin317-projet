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
    //gl_FragColor = vec4(0.326,0.346,0.630,1.000);
}
//! [0]

