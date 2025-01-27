/*
This file is part of FlashMQ (https://www.flashmq.org)
Copyright (C) 2021-2023 Wiebe Cazemier

FlashMQ is free software: you can redistribute it and/or modify
it under the terms of The Open Software License 3.0 (OSL-3.0).

See LICENSE for license details.
*/

#ifndef CIRBUF_H
#define CIRBUF_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <cassert>
#include <algorithm>

// Optimized circular buffer, works only with sizes power of two.
class CirBuf
{
#ifdef TESTING
    friend class MainTests;
#endif

    char *buf = NULL;
    uint32_t head = 0;
    uint32_t tail = 0;
    uint32_t size = 0;

    bool primedForSizeReset = false;
public:

    CirBuf(size_t size);
    ~CirBuf();

    uint32_t usedBytes() const;
    uint32_t freeSpace() const;
    uint32_t maxWriteSize() const;
    uint32_t maxReadSize() const;
    char *headPtr();
    char *tailPtr();
    void advanceHead(uint32_t n);
    void advanceTail(uint32_t n);
    char peakAhead(uint32_t offset) const;
    void ensureFreeSpace(size_t n, const size_t max = UINT_MAX);
    void doubleSize(uint factor = 2);
    uint32_t getSize() const;

    void resetSizeIfEligable(size_t size);
    void resetSize(size_t size);
    void reset();

    void write(const void *buf, size_t count);
    std::vector<char> readToVector(const uint32_t max);
    std::vector<char> readAllToVector();

    bool operator==(const CirBuf &other) const;
};

#endif // CIRBUF_H
