//
// Created by lightol on 18-6-10.
//

#ifndef NUMBERCLUSTER_CLUSTER_H
#define NUMBERCLUSTER_CLUSTER_H

#include <vector>

struct BRANCHER
{
    int rank;           // 这个分舵主在门派中是什么级别（堂主、长老还是总舵主？或者只是个小弟）
    int headquarter;    // 这个分舵主的总舵主是谁
    int headcount;      // 门派里总共有多少人
};

class cluGraph
{
public:
    cluGraph(int humanNums): branches(humanNums)
    {
        branchers.resize(humanNums);  // 各自为阵，每个人都建立一个分舵

        for(int i = 0; i < humanNums; ++i)
        {
            branchers[i].rank = 0;
            branchers[i].headcount = 1;
            branchers[i].headquarter = i;  // 总舵主就是自己
        }
    }

    // find clusterID for vertex node
    int findHeadquarter(int id)
    {
        int y = id;

        // 第id个分舵的总舵主不是自己
        while(id != branchers[id].headquarter)  // 分舵主的上级就是自己了，那么说明它是总舵主
            id = branchers[id].headquarter;  // 找找它的总舵主是谁

            // 现在你给我记住，你的总舵主就是id
        branchers[y].headquarter = id;  // 把帮主的id存在这个节点的心里，下次就可以绕过分舵主，直接搜寻到总舵主了
        return id;
    }

    // joins two vertexs into one cluster
    void join(int x, int y)
    {
        // 如果荆门分舵的级别高于钟祥分舵，那么钟祥分舵就应该归入荆门分舵
        if(branchers[x].rank > branchers[y].rank)
        {
            branchers[y].headquarter = x;  // y拜x为分舵主，相当于天鹰教归入明教
            branchers[x].headcount += branchers[y].headcount; // y分舵的小弟全部归属给x
        }
        else
        {
            branchers[x].headquarter = y;  // x拜y为分舵主
            branchers[y].headcount += branchers[x].headcount;
            if(branchers[x].rank == branchers[y].rank)  // 本来已经收了x，y应该比x高一级，如果不高的话就升官
                branchers[y].rank++;
        }
        branches--;  // 从此以后，只有明教，没有天鹰教
    }

private:
    int branches;  // 总共有多少个分舵
    std::vector<BRANCHER> branchers;  // 所有的分舵
};
#endif //NUMBERCLUSTER_CLUSTER_H
