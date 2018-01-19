#include <string>

class TextureLoader
{
    public:
        TextureLoader();
        TextureLoader(const std::string);

        void setFile(const std::string);
        int readFile();
        void **getBuffer();
};
