#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec4 a_position;

varying vec2 v_texcoord;

varying vec3 terrain_color;


//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;


    if (a_position.z > 1.1) // neige
    {
       terrain_color = vec3(1.0, 1.0, 1.0);
    }

    else if (a_position.z > 0.8) // neige moins blanche
    {
       terrain_color = vec3(0.9, 0.9, 0.9);
    }

    else if (a_position.z < 0.60) // eau gelee
    {
       terrain_color = vec3(0.7, 0.7, 0.85);
    }

    else // végétation enneigee
    {
        terrain_color = vec3(0.6, 0.9, 0.6);
    }
}
//! [0]
