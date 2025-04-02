cbuffer global : register(b5)
{
    float4 gConst[32];
};

cbuffer frame : register(b4)
{
    float4 time;
    float4 aspect;
};

cbuffer camera : register(b3)
{
    float4x4 world[2];
    float4x4 view[2];
    float4x4 proj[2];
};

cbuffer drawMat : register(b2)
{
    float4x4 model;
    float hilight;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 vpos : POSITION0;
    float4 wpos : POSITION1;
    float4 vnorm : NORMAL1;
    float2 uv : TEXCOORD0;
};

float3 rotY(float3 pos, float a)
{
    float3x3 m =
    {
        cos(a), 0, sin(a),
        0, 1, 0,
        -sin(a), 0, cos(a)
    };
    pos = mul(pos, m);
    return pos;
}

VS_OUTPUT VS(uint vID : SV_VertexID)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    float2 quadUI[4] = {0,0,1,0,1,1,0,1};
    float3 quad[8];
    quad[0] = float3(1, -1, -1);
    quad[1] = float3(1, 1, -1);
    quad[2] = float3(-1, 1, -1);
    quad[3] = float3(-1, -1, -1);
    quad[4] = float3(1, -1, 1);
    quad[5] = float3(1, 1, 1);
    quad[6] = float3(-1, 1, 1);
    quad[7] = float3(-1, -1, 1);


    int ind[36] = {
    0, 1, 3,
    1, 2, 3,
    1, 5, 2,
    5, 6, 2,
    5, 4, 6,
    4, 7, 6,
    4, 1, 0,
    4, 5, 1,
    4, 0, 7,
    0, 3, 7,
    3, 2, 6,
    3, 6, 7 };


    int v = ind[vID];

    float4 pos = float4(quad[v], 1);


    
    
    output.pos = mul(pos, mul(view[0], proj[0]));
    float2 p = quadUI[vID%4];
    output.uv = p;
    return output;
}
