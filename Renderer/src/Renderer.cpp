#include <Renderer.h>
#include <iostream>
#include <fstream>
#include <string>

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include <simd/simd.h>

Renderer::Renderer( MTL::Device* pDevice )
: _pDevice( pDevice->retain() )
{
    _pCommandQueue = _pDevice->newCommandQueue();
    buildShaders();
    buildBuffers();
}

Renderer::~Renderer()
{
    _pVertexPositionsBuffer->release();
    _pVertexColorsBuffer->release();
    _pPSO->release();
    _pCommandQueue->release();
    _pDevice->release();
}

void Renderer::buildShaders()
{
     std::ifstream in("/Users/kiseop/development/KSRenderer/Renderer/shader/shader.metal");
     std::string shaderSource;
     if (in.is_open()) {
          in.seekg(0, std::ios::end);
          int size = in.tellg();
          shaderSource.resize(size);
          in.seekg(0, std::ios::beg);
          in.read(&shaderSource[0], size);
     } 
     else
          std::cout << "cannot find shader file.." << std::endl;
  
    NS::Error* pError = nullptr;
    MTL::Library* pLibrary = _pDevice->newLibrary( NS::String::string(shaderSource.c_str(), NS::StringEncoding::UTF8StringEncoding), nullptr, &pError );
    if ( !pLibrary )
    {
        __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }

    MTL::Function* pVertexFn = pLibrary->newFunction( NS::String::string("vertexMain", NS::StringEncoding::UTF8StringEncoding) );
    MTL::Function* pFragFn = pLibrary->newFunction( NS::String::string("fragmentMain", NS::StringEncoding::UTF8StringEncoding) );

    MTL::RenderPipelineDescriptor* pDesc = MTL::RenderPipelineDescriptor::alloc()->init();
    pDesc->setVertexFunction( pVertexFn );
    pDesc->setFragmentFunction( pFragFn );
    pDesc->colorAttachments()->object(0)->setPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );

    _pPSO = _pDevice->newRenderPipelineState( pDesc, &pError );
    if ( !_pPSO )
    {
        __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }

    pVertexFn->release();
    pFragFn->release();
    pDesc->release();
    pLibrary->release();
}

void Renderer::buildBuffers()
{
     const size_t NumVertices = 4;
     simd::float3 positions[NumVertices] =
    {
        { -0.8f,  0.8f, 0.0f },
        { -0.8f, -0.8f, 0.0f },
        { 0.8f, -0.8f, 0.0f },
        { 0.8f, 0.8f, 0.0f }
    };

     uint16_t indices[] =  {
          0, 1, 2,
          2, 3, 0,
     };

    simd::float3 colors[NumVertices] =
    {
        {  1.0, 0.3f, 0.2f },
        {  0.8f, 1.0, 0.0f },
        {  0.8f, 1.0, 0.0f },
        {  0.8f, 0.0f, 1.0 }
    };

    const size_t positionsDataSize = NumVertices * sizeof( simd::float3 );
    const size_t colorDataSize = NumVertices * sizeof( simd::float3 );
    const size_t indexDataSize = sizeof(indices);


    MTL::Buffer* pVertexPositionsBuffer = _pDevice->newBuffer( positionsDataSize, MTL::ResourceStorageModeManaged );
    MTL::Buffer* pVertexColorsBuffer = _pDevice->newBuffer( colorDataSize, MTL::ResourceStorageModeManaged );
    MTL::Buffer* pIndexBuffer = _pDevice->newBuffer( indexDataSize, MTL::ResourceStorageModeManaged );
    MTL::Buffer* rot = _pDevice->newBuffer( sizeof( float ), MTL::ResourceStorageModeManaged );


    _pVertexPositionsBuffer = pVertexPositionsBuffer;
    _pVertexColorsBuffer = pVertexColorsBuffer;
    _pIndexBuffer = pIndexBuffer;
    _pRotBuffer = rot;

    memcpy( _pVertexPositionsBuffer->contents(), positions, positionsDataSize );
    memcpy( _pVertexColorsBuffer->contents(), colors, colorDataSize );
    memcpy( _pIndexBuffer->contents(), indices, indexDataSize );

    _pVertexPositionsBuffer->didModifyRange( NS::Range::Make( 0, _pVertexPositionsBuffer->length() ) );
    _pVertexColorsBuffer->didModifyRange( NS::Range::Make( 0, _pVertexColorsBuffer->length() ) );
    _pIndexBuffer->didModifyRange( NS::Range::Make( 0, _pIndexBuffer->length() ) );
}
void Renderer::SetRenderPassDescriptor(MTL::RenderPassDescriptor* pRpd)
{
    _pRpd = pRpd;
}
void Renderer::draw( CA::MetalDrawable* _renderTarget)
{
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = _pCommandQueue->commandBuffer();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( _pRpd );

    pEnc->setRenderPipelineState( _pPSO );
    pEnc->setVertexBuffer( _pVertexPositionsBuffer, 0, 0 );
    pEnc->setVertexBuffer( _pVertexColorsBuffer, 0, 1 );

    static float move;
    move +=0.001f;
    float s = sinf(move);
    memcpy( _pRotBuffer->contents(), &s, sizeof( float ) );
    _pRotBuffer->didModifyRange( NS::Range::Make( 0, _pRotBuffer->length() ) );
    pEnc->setVertexBuffer(_pRotBuffer, 0, 2);

    pEnc->drawIndexedPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle, 6, MTL::IndexType::IndexTypeUInt16, _pIndexBuffer, 0, 1);

    pEnc->endEncoding();
    pCmd->presentDrawable( _renderTarget );
    pCmd->commit();

    pPool->release();
}