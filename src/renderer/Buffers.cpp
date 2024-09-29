#include "Buffers.h"

/*

 _    __                 __                   ____             ____    ____              
| |  / /  ___    _____  / /_  ___    _  __   / __ )  __  __   / __/   / __/  ___    _____
| | / /  / _ \  / ___/ / __/ / _ \  | |/_/  / __  | / / / /  / /_    / /_   / _ \  / ___/
| |/ /  /  __/ / /    / /_  /  __/ _>  <   / /_/ / / /_/ /  / __/   / __/  /  __/ / /    
|___/   \___/ /_/     \__/  \___/ /_/|_|  /_____/  \__,_/  /_/     /_/     \___/ /_/     
                                                                                         
                                                                                                                                             
*/



VertexBufferObject::VertexBufferObject(float* vertices, unsigned int Size)
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ARRAY_BUFFER, Size, vertices, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &_rendererID);
}





/*
    ______    __                                   __     ____             ____    ____              
   / ____/   / /  ___    ____ ___   ___    ____   / /_   / __ )  __  __   / __/   / __/  ___    _____
  / __/     / /  / _ \  / __ `__ \ / _ \  / __ \ / __/  / __  | / / / /  / /_    / /_   / _ \  / ___/
 / /___    / /  /  __/ / / / / / //  __/ / / / // /_   / /_/ / / /_/ /  / __/   / __/  /  __/ / /    
/_____/   /_/   \___/ /_/ /_/ /_/ \___/ /_/ /_/ \__/  /_____/  \__,_/  /_/     /_/     \___/ /_/     
                                                                                                     
*/


ElementBufferObject::ElementBufferObject(unsigned int* Indices, unsigned int Size)
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
    glDeleteBuffers(1, &_rendererID);
}