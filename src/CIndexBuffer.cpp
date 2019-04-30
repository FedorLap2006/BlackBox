#include <BlackBox/CIndexBuffer.hpp>
#include <utility>


using namespace std;

CIndexBuffer::CIndexBuffer(const void *data, GLint size) :
  m_Data(data), m_Count(size)
{

}

CIndexBuffer::~CIndexBuffer()
{
}
