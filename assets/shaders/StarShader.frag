uniform float u_time;
uniform vec2 u_resolution;

#define NUM_LAYERS 8.0
#define TAU 6.28318
#define PI 3.141592
#define VELOCITY 0.008 //modified value to increse or decrease speed, negative value travel backwards
#define STAR_GLOW 0.019
#define STAR_SIZE 2.0
#define CANVAS_VIEW 25.0 // 20

// NEW DARK CORNER THING
const float MAX_CORNER = pow(0.2, 4);

float Star(vec2 uv, float flare){
    float d = length(uv);
  	float m = sin(STAR_GLOW*1.2)/d;  
    float rays = max(0.01, .3-abs(uv.x*uv.y*700.)); //float rays = max(0., .5-abs(uv.x*uv.y*1000.)); 
    m += (rays*flare)*2.;
    m *= smoothstep(1., .1, d); //    m *= smoothstep(1., .1, d);
    return m;
}

float Hash21(vec2 p){
    p = fract(p*vec2(123.34, 456.21));
    p += dot(p, p+45.32);
    return fract(p.x*p.y);
}

vec3 StarLayer(vec2 uv){
    vec3 col = vec3(0);
    vec2 gv = fract(uv);
    vec2 id = floor(uv);
    for(int y=-1;y<=1;y++){
        for(int x=-1; x<=1; x++){
            vec2 offs = vec2(x,y);
            float n = Hash21(id+offs);
            float size = fract(n);
            float star = Star(gv-offs-vec2(n, fract(n*34.))+.5, smoothstep(.1,.9,size)*.46);
            vec3 color = sin(vec3(.2,.3,.9)*fract(n*2345.2)*TAU)*.25+.75;
            color = color*vec3(.5,.59,.4+size); //.9
            star *= sin(u_time*.6+n*TAU)*.5+.5; //   star *= sin(u_time*.6+n*TAU)*.5+.5;
            col += star*size*color;
        }
    }
    return col;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy -0.5 * u_resolution.xy)/u_resolution.y;
	vec2 m = vec2(0);
    m -= vec2(m.x+sin(u_time*0.22), m.y-cos(u_time*0.22));
   
    m += (vec2(0.5)-u_resolution.xy * 0.5)/u_resolution.y;
    float t = u_time*VELOCITY; 
    vec3 col = vec3(0);  
    for(float i = 0.0; i < 1.0 ; i += 1.0 / NUM_LAYERS)
    {
        float depth = fract(i + t);
        float scale = mix(CANVAS_VIEW, 0.5, depth);
        float fade = depth * smoothstep(1.0 , 0.9, depth);
        col += StarLayer(uv * scale + i * 453.2 - u_time * 0.05 + m) * fade;
    }   

    vec4 finalColor = vec4(col,1.0);
   
    // NEW DARK CORNER THING
    vec2 offset = vec2(-.01);
    vec2 pos = (gl_FragCoord.xy - offset) / u_resolution;

    float vignette = pos.x * pos.y * (1.-pos.x) * (1.-pos.y);

    finalColor.rgb = finalColor.rgb * smoothstep(0, MAX_CORNER, vignette);

    gl_FragColor = finalColor;
}