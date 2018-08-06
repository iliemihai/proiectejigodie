#ifndef UTILS_H
#define UTILS_H
#include <cstddef>

class Utils{
public:
    static const std::size_t CalculatePadding(const std::size_t baseAddress, const std::size_t alignment) {
        const std::size_t multiplier = (baseAddress/alignment)+1;
        const std::size_t alignmentAddress = multiplier*alignment;
        const std::size_t padding = alignmentAddress - baseAddress;
        return padding;
}

    static const std::size_t CalculatePaddingWithHeader(const std::size_t baseAddress, const std::size_t alignment, const std::size_t headerSize) {
        std::size_t padding = CalculatePadding(baseAddress, alignment);
        std::size_t neededSpace = headerSize;

        if(padding < neededSpace) {
            //header does not fit, calculate next aligned address that header fits
            neededSpace -= padding;

            //how manny alignments I need to fit the header
            if(neededSpace % alignment > 0) {
                padding += alignment*(1+(neededSpace/alignment));
            } else {
                padding += alignment*(neededSpace/alignment);
            }
        }
        return padding;
    }

};

#endif
