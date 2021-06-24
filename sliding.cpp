#include<iostream>
#include<cmath>
using namespace std;

void print(int buf[],int base,int window,int bufsize)
{
    int index=base;
    for(int i=base; i<window; i++)
    {
        if(index>bufsize)
            index=0;

        cout<<buf[index]<<" ";
        index++;
    }
    cout<<endl;
}

int get_ack(int ack[],string station[],int event)
{
    int total=0;
    for(int i=0; i<=event; i++)
    {
        if(station[i]==station[event])
            total+=ack[i];
    }
    return total;
}

int main()
{
    int window,sequence,event,tb=0,tw=0,rb=0,rw=0,act_window,bufsize;

    cin>>sequence>>window;
    act_window=window;
    bufsize=pow(2,sequence)-1;

    int ack[bufsize],buf[bufsize];

    string station[bufsize+1];
    station[0]=" ";
    for(int i=0; i<=bufsize; i++)
    {
        ack[i]=0;
        buf[i]=i;
    }

    cout<<"At the beginning:\n";
    cout<<"X Transmitting buffer: ";
    print(buf,tb,window,bufsize);
    cout<<"X Transmitting Window: ";
    print(buf,tw,window,bufsize);
    cout<<"X Receiving buffer: ";
    print(buf,rb,window,bufsize);
    cout<<"X Receiving Window: ";
    print(buf,rw,window,bufsize);

    while(1)
    {
        cin>>event;

        if(event==-1)
            break;

        cin>>station[event];
        cin>>ack[event];


        if(event==1)
            tb=0;
        else if(station[1]==station[event])
            tb=get_ack(ack,station,event-2);
        else
            tb=get_ack(ack,station,event-1);

        if(station[1]==station[event])
            tw=get_ack(ack,station,event);
        else
            tw=get_ack(ack,station,event-1);

        if(station[1]!=station[event])
        {
            window=window+ack[event-1];
            while(window-tb<act_window || window-tw<act_window)
                window++;
        }
        cout<<"After event "<<event<<":\n";
        cout<<"X Transmitting buffer: ";
        print(buf,tb,window,bufsize);
        cout<<"X Transmitting Window: ";
        print(buf,tw,window,bufsize);

        if(ack[event]!=0 && station[1]!=station[event])
        {
            rw=ack[event];
            window=window-ack[event-1];
        }
        while(window-rb>act_window || window-rw>act_window)
            window--;
        cout<<"X Receiving buffer: ";
        print(buf,rb,window,bufsize);
        cout<<"X Receiving Window: ";
        print(buf,rw,window,bufsize);

        if(ack[event]!=0 && station[1]!=station[event])
        {
            rb=ack[event];
            window=window+ack[event-1];
        }
    }

}
