# -*- coding: utf-8 -*-
import sys
import random as rd
import numpy as np

mapSideLength = 50
AlreadyInClosePath = set()

def calcDst(a, b):
    npa = np.array(a)
    npb = np.array(b)
    return np.linalg.norm(npa - npb)

def getMST(t_map):
    low = [0.0 for i in range(mapSideLength + 1)]
    visited = [False for i in range(mapSideLength + 1)]
    visited[1] = True
    pos = 1
    total_length = 0.0
    result = []
    for i in range(1, mapSideLength + 1):
        if i != pos:
            low[i] = t_map[pos][i]
    # prim, i : 1~n-1, j: 1~n
    for i in range(1, mapSideLength):
        if i in AlreadyInClosePath:
            continue
        minDst = sys.maxint
        for j in range(1, mapSideLength + 1):
            if j in AlreadyInClosePath:
                continue
            if visited[j] is False and minDst > low[j]:
                minDst = low[j]
                pos = j
        # add the edge & correspongding points
        total_length += minDst
        result.append((i, j, minDst))
        visited[pos] = True
        for j in range(1, mapSideLength + 1):
            if visited[j] is False and low[j] > t_map[pos][j]:
                low[j] = t_map[pos][j]

    return (total_length, result)

def generateTSPpoints():
    global AlreadyInClosePath
    tsp_map = [[0.0 for col in range(mapSideLength + 1)] for row in range(mapSideLength + 1)]
    pointLocs = set()
    while (len(pointLocs) < mapSideLength + 1):
        pointLocs.add((rd.randint(1, mapSideLength), rd.randint(1, mapSideLength)))
    pointLocsTuple = tuple(pointLocs)
    for i in range(1, mapSideLength + 1):
        for j in range(i + 1, mapSideLength + 1):
            tsp_map[i][j] = tsp_map[j][i] = calcDst(pointLocsTuple[i], pointLocsTuple[j])
    # print map
    # print pointLocsTuple
    return (tsp_map, pointLocsTuple)


def tsp_search_astar(t_map):
    startPntIdx = rd.randint(1, mapSideLength)
    print 'choose start point as:', startPntIdx
    AlreadyInClosePath.add(startPntIdx)

    total_length = 0.0
    path = []
    path.append((startPntIdx, 0))
    last_idx = startPntIdx
    while (len(AlreadyInClosePath) < mapSideLength):
        # print 'now added[', len(AlreadyInClosePath), ']points'
        # calc costs and find the minimal one
        costArr = [sys.maxint for i in range(1, mapSideLength + 1)]
        # print 'calc MST of the left[', (mapSideLength - len(AlreadyInClosePath)), ']points'

        # calc Astar cost
        # MST of all un-added-to-path points
        (mst_length, result) = getMST(t_map)
        # the average of the dist(un-added-to-path points, startPnt)
        sumDist2Start = 0.0
        for i in range(1, mapSideLength + 1):
            if i in AlreadyInClosePath:
                continue
            sumDist2Start += t_map[i][startPntIdx]
        avg = sumDist2Start / (mapSideLength - len(AlreadyInClosePath))

        for i in range(1, mapSideLength):
            if i in AlreadyInClosePath:
                continue
            costArr[i] = mst_length + t_map[i][last_idx] + avg

        curBestChoiceIdx = costArr.index(min(costArr))
        AlreadyInClosePath.add(curBestChoiceIdx)
        # add to result path
        curLength = t_map[last_idx][curBestChoiceIdx]
        total_length += curLength
        last_idx = curBestChoiceIdx
        print 'choose Point of Index', curBestChoiceIdx
        path.append((curBestChoiceIdx, curLength))

    return (total_length, path)


if __name__ == '__main__':
    reload(sys)
    sys.setdefaultencoding('utf-8')
    (tsp_map, pointLocsTuple) = generateTSPpoints()
    (loop_length, loop_details) = tsp_search_astar(tsp_map)
    print ''
    print 'Finished.'
    print 'loop length:', loop_length
    pathStr = 'S'
    for singl in loop_details:
        pathStr = '->'.join([pathStr, str(singl[0])])
    print 'Path is :', pathStr

