﻿// Spanning_Trees.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


//최소 신장 트리

//신장트리란?
// 원래의 그래프의 모든 노드가 연결되어 있으면서 트리의 속성을 만족하는 그래프
// 신장트리의 조건
// 1. 본래의 그래프의 모든 노드를 포함해야함
// 2. 모든 노드가 서로 연결
// 3. 트리의 속성을 만족시킴(사이클이 존재하지 않음)

//최소신장트리
//Minimum Spanning Tree MST
// 가능한 신장트리중에서 간선의 가중치의 합이 최소한인 신장트리를 지칭한다.
//크르수칼 알고리즘, 프림알고리즘 이용

//최소 신장 트리 알고리즘
//-  크루스칼 알고리즘
// 모든 정점을 독립적인 집합으로 만든다.
// 모든 간선을 비용을 기준으로 정렬하고, 비용이 작은 간선부터, 양 끝의 두 정점을 비교한다. - 핵심 로직 
// 두 정점의 최상위 정점을 확인하고(파인드로직), 서로 다를 경우 두 정점을 연결한다. 최소 신장 트리는 사이클이 없으므로, 사이클이 생기지 않도록 하는 것임 - 사이클을 체크하는것이 어렵다
// - 사이클을 체크하기 위한 또다른 알고리즘을 사용 - 
// 탐욕 알고리즘을 기초로 하고 있음, 당장 눈앞의 최소 비용을 선택해서 결과적으로 최적의 솔루션을 찾음



//사이클을 체크하기 위한 방법
//Union-Find 알고리즘 이용
// 집합안에 연결할 노드가 같이 포함되어있다고 한다면 이것은 사이클이 생긴다고 말할 수 있다.
// visited 노드 찾는거랑 비슷한거같다.
// 양끝에있는 노드가 서로 다른 집합이면 연결해도 된다.

//Disjoint set을 표현할 때 사용하는 알고리즘으로 트리 구조를 활용하는 알고리즘
//간단하게 노드들 중에 연결된 노드를 찾거나, 노드들을 서로 연결할 때 합칠 때 사용
// 서로 중복되지 않는 집합들로 나눠진 원소들에 대한 정보를 저장하고 조작하는 자료구조
//공통원소가 없는 서로소 상호 배타적인 부분 집합들로 나눠진 원소들에 대한 자료구조를 의미함


//초기화
//n개의 원소가 개별 집합으로 이뤄지도록 초기화
//union
// 두 개별의 집합을 합치는 , 두 트리를 하나의 트리로 만듬 둘 중 하나의 루트노드를 합칠 트리의 루트 노드로 놓고 나머지를 자식으로 넣는다
//find
// 여러 노드가 존재할 때, 두개의 노드를 선택해서 현재 두 노드가 같은 그래프에 속하는지 판별하기 위해, 각 그룹의 최상단 원소 즉 루트 노드를 확인
// 각 다른 부분집합의 루트노드만 같은지 확인하면 아래도 같은 집합이 아닌지 맞는지 확인할 수 있다.

//유니온파인드 알고리즘의 고려할 점
// 유니언 순서에 따라서, 최악의 경우 링크드 리스트와 같은 형태가 될 수 있음
// 이 때는 find/union 시 계산량이 O(N)이 될 수 있으므로 해당문제를 해결하기 위해 union-by-rank , path compression 기법을 사용함

//uniom-by-rank 기법
// 각 트리에 대해 높이를 기억해두고
// 유니언시 두 트리의 높이가 다르면, 높이가 작은 트리를 높이가 큰 트리에 붙임 (즉, 높이가 큰 트리의 루트 노드가 합친 집함의 루트 노드가 되게함)
//
// 높이가 같을 때, 높이가 h-1인 두 개의 트리를 합칠 때는 한 쪽의 트리의 높이를 1 증가시켜주고 다른 쪽의 트리를 해당 트리에 붙여줌

//초기화 시 모든 원소의 높이는 0인 개별 집합인 상태에서 하나씩 원소를 합칠 때 유니언바이랭크 기법을 사용한다면
// 높이가 h인 트리가 만들어지려면 높이가 h-1인 두개의 트리가 합쳐져야함
// 높이가 h-1인 트리를 만들기 위해 최소 n개의 원소가 필요하다면 높이간 h인 트리가 만들어지기 위해서는 최소 2n개의 원소가 필요함
// 따라서 유니언바이랭크 기법을 사용하면, 시간복잡도를 O(logN)으로 낯출 수 있음;


//path-compression 기법
//find를 실행한 노드에서 거쳐간 노드를 루트에 다이렉트로 연결하는 기법
//find를 실행한 노드는 이후부터는 루트노드를 한번에 알 수 있음


//위 두가지의 기법을 조합하면 유니언파인드 알고리즘

//프림 알고리즘

//대표적인 최소 신장 알고리즘
// 시작 정점을 선택한 후, 정점에 인접한 간선중 최소 간선으로 연결된 정점을 선택하고, 해당 정점에서 다시 최소
//간선으로 연결된 정점을 선택하는 방식으로 최소 신장트리를 확장해가는 방식

//크루스칼은 노드가 연결되어있는지 신경안쓰고, 간선비용으로 소트한 후 찾아내기
//프림은 이미 연결되어 있는 것에서 찾는다. 
//둘 다 탐욕 알고리즘을 기반으로 하고 있다. 


//1. 임의의 정점을 선택, 연결된 노드 집합에 삽입
//2. 선택된 정점에 연결된 간선들을 간선리스트에 삽임
//3. 간선 리스트에서 최소 가중치를 가지는 간선부터 추출해서.
// - 해당 간선에 연결된 인접 정점이 연결된 노드 집합에 들어있다면, 스킵합 (싸이클을 막기위함)
// - 해당 간선에 연결된 인접 정점이 연결되 노드 집합에 들어있지 않다면, 해당 간선을 선택하고, 최소 신장트리에 삽입
//4. 추출한 간선은 간선리스트에서 제거
//5. 간선 리스트에 더 이상의 간선이 없을 때까지 3~4번을 반복




#include <iostream>

using namespace std;

int main()
{
   
}
