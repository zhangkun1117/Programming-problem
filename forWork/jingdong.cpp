#include <iostream>

#include <cstdio>

#include <vector>

#include <set>

#define FRE



using namespace std;



int T;

int N,M;



int main()

{

    #ifdef FRE

    freopen("in.txt","r",stdin);

    #endif // FRE



    scanf("%d",&T);

    for(int t=0;t<T;++t){

        // T组数据

        //printf("\nNext Data:\n");

        scanf("%d%d",&N,&M);

        //printf("N: %d, M: %d\n",N,M);

        vector<set<int> > numMap(N+1);

        vector<vector<int> > numsMap(N+1);

        vector<vector<int> > group;

        for(int i=0;i<M;++i){

            int x,y;

            scanf("%d%d",&x,&y);

            //numMap[x].push_back(y);

            numMap[x].insert(y);

            numMap[y].insert(x);

            //printf("x: %d , y: %d\n",x,y);



        }



        for(int i=1;i<=N;++i){

            //printf("i: %d -> ",i);

            int j=0;

            for(set<int>::iterator it=numMap[i].begin();it!=numMap[i].end();++it){

            //for(int j=0;j<numMap[i].size();++j){

                numsMap[i].push_back(*it);

                //printf("%d , ",*it);

                //printf("%d , ",numsMap[i][j]);

                ++j;

            }

            //printf("\n");

        }



        for(int i=1;i<=N;++i){

            vector<int> flag(N+1,0);

            flag[0] = 1;

            flag[i] = 1;

            if(group.size()==0){

                group.push_back(flag);

            }else{

                int save = 1;

                for(int g=0;g<group.size();++g){

                    save = 1;

                    for(int j=0;j<numsMap[i].size();++j){

                        if(group[g][numsMap[i][j]] == 1){

                            save = 0;

                            break;

                        }

                    }

                    if(save){

                        group[g][i] = 1;

                        group[g][0]++;

                        break;

                    }

                }

                if(save==0){

                    // 所有组都排斥它，新建一个组

                    group.push_back(flag);

                }

            }

        }

        int isC = 1;

        for(int g=0;g<group.size();++g){

            int left = N-group[g][0];

            //printf("g: %d  left: %d   size: %d  ",g+1,left,group[g][0]);

            for(int i=1;i<=N;++i){

                if(group[g][i]==1){

                    if(numsMap[i].size()!=left){

                        isC = 0;

                        break;

                    }

                    //printf("%d , ",i);

                }

            }

            //printf("\n");

            if(isC==0)break;

        }

        if(isC)printf("Yes\n");

        else printf("No\n");

        //printf("No\n");







    }





    return 0;

}

//京东笔试题
/*
int main(){
    int n;
    cin>>n;
    vector<vector<int> > arr(n,vector<int>(3,0));
    for(int i=0;i<n;i++){
        cin>>arr[i][0]>>arr[i][1]>>arr[i][2];
    }
    int sum =0; 
    for(int i=0;i<n;i++){
        int num=0;
        for(int j=0;j<n;j++){
            if(i ==j)
                num++;
            if(arr[i][0]<arr[j][0] && arr[i][1]<arr[j][1] && arr[i][2]<arr[j][2]){
                num++;
            }else{
                break;
            }
        }
        if(num == n) sum++;
    }
    cout<<sum<<endl;
    return 0;
}
*/