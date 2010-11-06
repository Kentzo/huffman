#pragma once

template<typename ELEMENT_TYPE>
struct DepthCounterNode {
    bool isLeaf;
    union {
        struct {
            DepthCounterNode* left;
            DepthCounterNode* right;
        };
        struct {
            ELEMENT_TYPE element;
            size_t depth;
        };
    };

    DepthCounterNode(DepthCounterNode* l, DepthCounterNode* r) : isLeaf(false), left(l), right(r) {
        left->incDepth();
        right->incDepth();
    }
    DepthCounterNode(const ELEMENT_TYPE& elem) : isLeaf(true), element(elem), depth(0) {}
    void incDepth() {
        if (!isLeaf) {
            left->incDepth();
            right->incDepth();
        }
        else {
            ++depth;
        }
    }
    void decDepth() {
        if (!isLeaf) {
            left->decDepth();
            right->decDepth();
        }
        else {
            --depth;
        }
    }
};
