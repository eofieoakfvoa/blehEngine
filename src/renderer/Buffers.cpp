#include "Buffers.h"

/*

 _    __                 __                   ____             ____    ____              
| |  / /  ___    _____  / /_  ___    _  __   / __ )  __  __   / __/   / __/  ___    _____
| | / /  / _ \  / ___/ / __/ / _ \  | |/_/  / __  | / / / /  / /_    / /_   / _ \  / ___/
| |/ /  /  __/ / /    / /_  /  __/ _>  <   / /_/ / / /_/ /  / __/   / __/  /  __/ / /    
|___/   \___/ /_/     \__/  \___/ /_/|_|  /_____/  \__,_/  /_/     /_/     \___/ /_/     
                                                                                         
                                                                                                                                             
*/



VertexBufferObject::VertexBufferObject(const void* Data, unsigned int Size)
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_DYNAMIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &_rendererID);
}





/*
    ____               __                  ____             ____    ____              
   /  _/   ____   ____/ /  ___    _  __   / __ )  __  __   / __/   / __/  ___    _____
   / /    / __ \ / __  /  / _ \  | |/_/  / __  | / / / /  / /_    / /_   / _ \  / ___/
 _/ /    / / / // /_/ /  /  __/ _>  <   / /_/ / / /_/ /  / __/   / __/  /  __/ / /    
/___/   /_/ /_/ \__,_/   \___/ /_/|_|  /_____/  \__,_/  /_/     /_/     \___/ /_/     
                                                                                      
*/


IndexBufferObject::IndexBufferObject(const void* Data, unsigned int Size)
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, 0, GL_STATIC_DRAW);
}

IndexBufferObject::~IndexBufferObject()
{
    glDeleteBuffers(1, &_rendererID);
}