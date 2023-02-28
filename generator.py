# #!/usr/bin/env python3

# import sys
# import random

# num = 1000
# for i in range(num):
# 	random.seed(i)
# 	in_path = "in/" + str(i).zfill(4) + ".txt"

# 	D = 365
# 	c = [random.randrange(0, 101) for _ in range(26)]
# 	s = [[random.randrange(0, 20001) for _ in range(26)] for _ in range(D)]
# 	with open(in_path, 'w') as f:

# 		print(D, file=f)
# 		print(" ".join(map(str, c)), file=f)
# 		for sd in s:
# 			print(" ".join(map(str, sd)), file=f)
# 		f.close()



# #include <bits/stdc++.h>
# #include <random>
# using namespace std;
# typedef long long int ll;
# typedef long double ld;
# #define rep(i, N) for(ll i = 0; i < (ll)N; i++)

# const ll D = 365;
# const ll N = 26;
# vector<ll> C(N);
# vector<vector<ll>> S(D, vector<ll>(N));

# struct State {
#     vector<ll> contests;
#     ll score;
#     State() {
#         vector<ll> _contests(D);
#         rep(i, D) _contests[i] = rand()%N;
#         contests = _contests;
#     }

#     ll get_score() {
#         score = 0;
#         vector<ll> last(N, -1);
#         rep(d, D) {
#             score += S[d][contests[d]];
#             last[contests[d]] = d;
#             rep(i, N) {
#                 score -= C[i] * (d - last[i]);
#             }
#         }
#         return score;
#     }
# };


# int main() {
#     clock_t start = clock();
#     ll _; cin >> _;
#     rep(i, N) cin >> C[i];
#     rep(i, D) rep(j, N) cin >> S[i][j];
#     State state = State();
#     while(true) {
#         clock_t end = clock();
#         ld time = (end - start) / CLOCKS_PER_SEC;
#         if(time > 2.0) break;
#         ll old_score = state.get_score();
#         ll idx1 = rand()%D;
#         ll idx2 = rand()%D;
#         swap(state.contests[idx1], state.contests[idx2]);
#         ll new_score = state.get_score();
#         if(new_score > old_score) {
#             continue;
#         }else {
#             swap(state.contests[idx1], state.contests[idx2]);
#         }
#     }
#     cerr << 1000000 + state.get_score() << endl;
#     rep(i, D) {
#         cout << state.contests[i] + 1 << endl;
#     }
# }













#include <bits/stdc++.h>
#include <random>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define rep(i, N) for(ll i = 0; i < (ll)N; i++)

const ll D = 365;
const ll N = 26;
vector<ll> C(N);
vector<vector<ll>> S(D, vector<ll>(N));

struct State {
    vector<ll> contests;
    vector<ll> scores;
    State() : scores(N, -1e9) {
        vector<ll> _contests(D);
        rep(i, D) _contests[i] = rand()%N;
        contests = _contests;
    }

    void get_diff_score(ll idx) {

        ll last = -1;
        rep(d, D) {
            if(contests[d] == idx) {
                scores[idx] += S[d][contests[d]];
                last = d;
            }
            scores[idx] -= C[idx] * (d - last);
        }
    }

    ll get_score() { // O(10**4)
        vector<ll> last(N, -1);
        rep(i, N) scores[i] = 0;
        rep(d, D) {
            scores[contests[d]] += S[d][contests[d]];
            last[contests[d]] = d;
            rep(i, N) {
                scores[i] -= C[i] * (d - last[i]);
            }
        }
        ll a  =0;
        rep(i, N) a += scores[i];
return a;
        
    }

    // bool swap(ll idx1, ll idx2) {
    //     if(idx1 == idx2) return false;

        
    // }
    // bool move(ll idx, ll cnt) {
    //     if(contests[idx] == cnt) return false;
    // }
};


int main() {
    clock_t start = clock();
    ll _; cin >> _;
    rep(i, N) cin >> C[i];
    rep(i, D) rep(j, N) cin >> S[i][j];
    State state = State();
    while(true) {
        clock_t end = clock();
        ld time = (ld)(end - start) / CLOCKS_PER_SEC;
        if(time > 1.0) break;
        ll old_score = state.get_score();
        ll idx1 = rand()%D;
        ll idx2 = rand()%D;
        swap(state.contests[idx1], state.contests[idx2]);
        ll new_score = state.get_score();
        if(new_score > old_score) {
            continue;
        }else {
            swap(state.contests[idx1], state.contests[idx2]);
        }
    }
    cerr << 1000000 + state.get_score() << endl;
    rep(i, D) {
        cout << state.contests[i] + 1 << endl;
    }
}