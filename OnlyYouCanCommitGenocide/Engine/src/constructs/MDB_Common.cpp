#include "../../headers/constructs/MDB_Common.hpp"

void MDB_Common::get_resource_path(char* & point, char* directory)
{
#ifdef _WIN32
    const char PATH_SEP = '\\';

#else
    const char PATH_SEP = '/';
#endif

    if (point == nullptr)
    {
        std::string path;
        char *base_path = SDL_GetBasePath();
        if (base_path)
        {
            path = base_path;
            SDL_free(base_path);
        }
        else
        {
            throw MDB_SDL_Exception();
        }

        size_t pos = path.rfind(directory);
        path = path.substr(0, pos) + directory + PATH_SEP + "res" + PATH_SEP + '\0';
        pos = path.rfind(PATH_SEP)+1;

        point = new char[pos];
        memcpy_s(point, pos, path.c_str(), pos);
        point[pos] = '\0';

    }
    
}

MDB_File* MDB_Common::get_file_for_reading(char* file_name, uint32_t file_type)
{
    return get_file(SDL_RWFromFile(file_name, "rb"), MDB_E_FILE_IO_R, file_type);
}

MDB_File* MDB_Common::get_file_for_writing(char* file_name, uint32_t file_type)
{
    return get_file(SDL_RWFromFile(file_name, "w+b"), MDB_E_FILE_IO_W, file_type);
}

MDB_File* MDB_Common::get_file_for_readwrite(char* file_name, uint32_t file_type)
{
    return get_file(SDL_RWFromFile(file_name, "w+b"), MDB_E_FILE_IO_RW, file_type);
}

class MDB_File* MDB_Common::get_file_for_rw(char* file_name, char* mode, uint32_t mdb_file_mode, uint32_t file_type)
{
    return get_file(SDL_RWFromFile(file_name, mode), mdb_file_mode, file_type);
}

MDB_File* MDB_Common::get_file(SDL_RWops* file, uint32_t mode, uint32_t file_type)
{
    return new MDB_File(file, mode, file_type);
}

void MDB_Common::pack_char_array(char*& byte_array, uint8_t bytes, ...)
{
    va_list byte_list;
    va_start(byte_list, bytes);
    for (int i = 0; i < bytes; ++i)
    {
        byte_array[i] = va_arg(byte_list, uint8_t);
    }
    va_end(byte_list);
}


MDB_Point2f::MDB_Point2f() : x(0.0f), y(0.0f)
{
}

MDB_Point2f::MDB_Point2f(float x, float y) : x(x), y(y)
{
}

MDB_Point2f::MDB_Point2f(const MDB_Point2f& rhs) : x(rhs.x), y(rhs.y)
{
}

MDB_Point2f::MDB_Point2f(const MDB_Vector2f& rhs) : x(rhs.x), y(rhs.y)
{
}

MDB_Point2f MDB_Point2f::operator+(const MDB_Point2f& rhs) const
{
    return MDB_Point2f(x + rhs.x, y + rhs.y);
}

MDB_Point2f MDB_Point2f::operator+(const MDB_Vector2f& rhs) const
{
    return MDB_Point2f(x + rhs.x, y + rhs.y);
}

MDB_Point2f& MDB_Point2f::operator+=(const MDB_Vector2f& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}

MDB_Point2f MDB_Point2f::operator-(const MDB_Point2f& rhs) const
{
    return MDB_Point2f(x - rhs.x, y - rhs.y);
}

MDB_Point2f MDB_Point2f::operator-(const MDB_Vector2f& rhs) const
{
    return MDB_Point2f(x - rhs.x, y - rhs.y);
}

MDB_Point2f MDB_Point2f::operator-=(const MDB_Vector2f& rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;

    return *this;
}

MDB_Point2f MDB_Point2f::operator*(const float& rhs) const
{
    return MDB_Point2f(x * rhs, y * rhs);
}

MDB_Point2f MDB_Point2f::operator*(const MDB_Vector2f& rhs) const
{
    return MDB_Point2f(x * rhs.x, y * rhs.y);
}

MDB_Point2f MDB_Point2f::operator/(const float& rhs) const
{
    return MDB_Point2f(x / rhs, y / rhs);
}

MDB_Point2f MDB_Point2f::operator/(const MDB_Vector2f& rhs) const
{
    return MDB_Point2f(x / rhs.x, y / rhs.y);
}

MDB_Point2f MDB_Point2f::operator=(const MDB_Point2f& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    this->x = rhs.x;
    this->y = rhs.y;

    return *this;
}

float MDB_Point2f::dist_between(MDB_Point2f& rhs) const
{
    return MDB_Vector2f(this->x - rhs.x, this->y - rhs.y).get_magnitude();
}

MDB_Vector2f MDB_Point2f::vector_between(MDB_Point2f& rhs) const
{
    return MDB_Vector2f(this->x - rhs.x, this->y - rhs.y).normalise();
}

MDB_Vector2f::MDB_Vector2f() : x(0), y(0)
{
}

MDB_Vector2f::MDB_Vector2f(float x, float y) : x(x), y(y)
{
}

MDB_Vector2f MDB_Vector2f::operator+(const MDB_Vector2f& rhs) const
{
    return MDB_Vector2f(x + rhs.x, y + rhs.y);
}

MDB_Vector2f MDB_Vector2f::operator+=(const MDB_Vector2f& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}

MDB_Vector2f MDB_Vector2f::operator-(const MDB_Vector2f& rhs) const
{
    return MDB_Vector2f(x - rhs.x, y - rhs.y);
}

MDB_Vector2f MDB_Vector2f::operator*(const float& rhs) const
{
    return MDB_Vector2f(x * rhs, y * rhs);
}

MDB_Vector2f MDB_Vector2f::operator/(const float& rhs) const
{
    return MDB_Vector2f(x / rhs, y / rhs);
}

float MDB_Vector2f::dot_product(const MDB_Vector2f& rhs) const
{
    return (x * rhs.x) + (y * rhs.y);
}

MDB_Vector2f MDB_Vector2f::operator=(const MDB_Vector2f& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    x = rhs.x;
    y = rhs.y;
    return *this;
}

bool MDB_Vector2f::operator==(const MDB_Vector2f& rhs) const
{
    return (x == rhs.x) && (y == rhs.y);
}

bool MDB_Vector2f::operator!=(const MDB_Vector2f& rhs) const
{
    return (x != rhs.x) || (y != rhs.y);
}

MDB_Vector2f MDB_Vector2f::normalise() const
{
    return *this / get_magnitude();
}

float MDB_Vector2f::get_magnitude() const
{
    return sqrt(pow(x, 2) + pow(y, 2));
}
