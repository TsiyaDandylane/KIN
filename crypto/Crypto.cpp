#include <iostream>
#include <vector>
using namespace std;

class Crypto
{
private:
    string enKey;

public:
    Crypto()
    {
        enKey = "10761260708786482116";
    }

    int kin(int c0, int m0, int u, int k)
    {
        if(k<=1||u<=1)return 1;
        if(c0==0&&m0==0)return 1;


        int c = c0;
        int m = m0;
        int mo = 0;
        while (true)
        {
            int X = u*c + m;
            c = X % k;
            m = X / k;
            mo++;
            if (c == c0 && m == m0)
            {
                return mo;
            }
        }
    }

    string encrypt(string ume, string key)
    {
        vector<int> us;
        int klen = key.length();
        int len1 = klen - klen/2;
        int len2 = klen/2;
        vector<int> k1s;
        vector<int> k2s;

        for (int i = 0; i < ume.length(); i++)
        {
            int a = ume[i];
            while(a!=0)
            {
                us.push_back(a%10);
                a/=10;
            }
        }
        for (int i = 0; i < len1; i++)
        {
            int a = key[i];
            while(a!=0)
            {
                k1s.push_back(a%10);
                a/=10;
            }
        }
        for(int i = 0; i < len2; i++)
        {
            int a = key[i+len1];
            while(a!=0)
            {
                k2s.push_back(a%10);
                a/=10;
            }
        }
        string en = "";

        int ulen = us.size();
        int k1len = k1s.size();
        int k2len = k2s.size();
        int r = 0;
        int uidx = 0;
        int k1idx = 0;
        int k2idx = 0;
        while(k1idx<k1len||k2idx<k2len)
        {
            int u;
            int k1;
            int k2;
            if(r%3==0)
            {
                u = us[uidx%ulen];    
                uidx++;
                k1 = k1s[k1idx%k1len];
                k1idx++;
                k2 = k2s[k2idx%k2len] + 10*k2s[(k2idx+1)%k2len] + 100*k2s[(k2idx+2)%k2len];
                k2idx+=3; 
                r++;
            }
            else if(r%3==1)
            {
                u = us[uidx%ulen]+10*us[(uidx+1)%ulen];
                uidx+=2;
                k1 = k1s[k1idx%k1len] + 10*k1s[(k1idx+1)%k1len];
                k1idx+=2;
                k2 = k2s[k2idx%k2len] + 10*k2s[(k2idx+1)%k2len];
                k2idx+=2; 
                r++;
            }
            else
            {
                u = us[uidx%ulen]+10*us[(uidx+1)%ulen]+100*us[(uidx+2)%ulen];
                uidx+=3;
                k1 = k1s[k1idx%k1len] + 10*k1s[(k1idx+1)%k1len] + 100*k1s[(k1idx+2)%k1len];
                k1idx+=3;
                k2 = k2s[k2idx%k2len];
                k2idx++; 
                r++;
            }
            int kin1 = kin(0,1,u,k1);
            int kin2 = kin(0,1,u,k2);
            en += to_string(kin1+kin2);
        }
        return en;
    }
    
    bool right(string ume, string key)
    {
        if(encrypt(ume, key) == enKey)
        {
            return true;
        }
        else
        {   
            return false;   
        }
    }
};

int main()
{
    Crypto c;
    string key;
    while(true)
    {
        cout<<"请输入密钥：";
        cin>>key;
        if(c.right("1234", key))
        {
            cout<<"密钥正确！"<<endl;
            break;
        }
        else
        {
            cout<<"密钥错误！"<<endl;
        }
    }
    return 0;
}
