//
// Created by lightol on 18-6-10.
//

#ifndef NUMBERCLUSTER_CLUSTER_H
#define NUMBERCLUSTER_CLUSTER_H

#include <vector>

struct VERTEX
{
    int rank_;       // 这个分舵主在门派中是什么级别（堂主、长老还是总舵主？或者只是个小弟）
    int clusterID_;  // 这个分舵主的总舵主是谁
    int size_;       // 门派里总共有多少人
};

class cluGraph
{
public:
    cluGraph(int vertexNum): vertexNum_(vertexNum)
    {
        vertexs_.resize(vertexNum);

        for(int i = 0; i < vertexNum; ++i)
        {
            vertexs_[i].rank_ = 0;
            vertexs_[i].size_ = 1;
            vertexs_[i].clusterID_ = i;  // 帮主
        }
    }

    // find clusterID for vertex node
    int findCluID(int vertexID)
    {
        int y = vertexID;

        // 第vertexID个节点的分舵主不是自己
        while(vertexID != vertexs_[vertexID].clusterID_)  // 分舵主的上级就是自己了，那么说明它是总舵主
            vertexID = vertexs_[vertexID].clusterID_;  // 找找它的分舵主是谁

        vertexs_[y].clusterID_ = vertexID;  // 把帮主的id存在这个节点的心里，下次就可以绕过分舵主，直接搜寻到总舵主了
        return vertexID;
    }

    // joins two vertexs into one cluster
    void join(int x, int y)
    {
        if(vertexs_[x].rank_ > vertexs_[y].rank_)
        {
            vertexs_[y].clusterID_ = x;  // y拜x为分舵主，相当于天鹰教归入明教
            vertexs_[x].size_ += vertexs_[y].size_; // y分舵的小弟全部归属给x
        }
        else
        {
            vertexs_[x].clusterID_ = y;  // x拜y为分舵主
            vertexs_[y].size_ += vertexs_[x].size_;
            if(vertexs_[x].rank_ == vertexs_[y].rank_)  // 本来已经收了x，y应该比x高一级，如果不高的话就升官
                vertexs_[y].rank_++;
        }
        vertexNum_--;  // 从此以后，只有明教，没有天鹰教
    }

    int size(int x) const { return vertexs_[x].size_; }

private:
    int vertexNum_;
    std::vector<VERTEX> vertexs_;
};
#endif //NUMBERCLUSTER_CLUSTER_H
