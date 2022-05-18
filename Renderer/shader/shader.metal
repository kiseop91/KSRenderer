#include <metal_stdlib>
using namespace metal;

struct v2f
{
    float4 position [[position]];
    half3 color;
};

v2f vertex vertexMain( uint vertexId [[vertex_id]],
                        device const float3* positions [[buffer(0)]],
                        device const float3* colors [[buffer(1)]] ,
                        device const float* rot [[buffer(2)]]
                        )
{
    v2f o;
    o.position = float4( positions[ vertexId ] , 1.0 );
    o.position.x += *rot;
    o.color = half3 ( colors[ vertexId ] * (*rot) );
    return o;
}

half4 fragment fragmentMain( v2f in [[stage_in]] )
{
    return half4( in.color, 1.0 );
}
    