#include <iostream>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <QString>
#include <QDebug>

using namespace std;
void showInBit(int num);
bool check (unsigned char* buf);
void protocol (int num);


ofstream output;
int main()
{
    system("CLS");
    unsigned char *buf=new unsigned char[4];
    unsigned char *temp_ch=new unsigned char;
    fstream file;

    //Пути к файлам!!!
    output.open("D://Bunin/VNO_Dombrovsky/out.txt", ios::out );
    file.open("D://Bunin/VNO_Dombrovsky/mix.cap", ios::binary|ios::in|ios::out);
    file.read((char*)buf, 3);
    int count=0;
    cout<<"Working..."<<endl;
    cout<<"Found packets: "<<count;
    while (file.gcount()>0)
    {
        bool ret=check(buf);
        if (ret==true)
        {
            count++;
            cout<<"\r";
            cout<<"Found packets: "<<count;
//            cout<<"Packet "<<dec<<count<<":"<<endl;
            output<<"Packet "<<dec<<count<<":";
            file.read((char*)temp_ch, 1);
            int temp=static_cast<int>(*temp_ch);
            int priority=temp>>5;
//            cout<<endl<<"Priority: "<<dec<<priority<<endl;
            output<<endl<<"Priority: "<<dec<<priority<<endl;
            int byte=temp&16;
            if (byte==0)
            {
//                cout<<"Delay: 0 - normal"<<endl;
                output<<"Delay: 0 - normal"<<endl;
            }
            else
            {
//                cout<<"Delay: 1 - low"<<endl;
                output<<"Delay: 1 - low"<<endl;
            }
            byte=temp&8;
            if (byte==0)
            {
//                cout<<"Throughput: 0 - low"<<endl;
                output<<"Throughput: 0 - low"<<endl;
            }
            else
            {
//                cout<<"Throughput: 1 - high"<<endl;
                output<<"Throughput: 1 - high"<<endl;
            }
            byte=temp&4;
            if (byte==0)
            {
//                cout<<"Reliability: 0 - normal"<<endl;
                output<<"Reliability: 0 - normal"<<endl;
            }
            else
            {
//                cout<<"Reliability: 1 - high"<<endl;
                output<<"Reliability: 1 - high"<<endl;
            }
            byte=temp&3;
            if (byte==0)
            {
//                cout<<"Explicit Congestion Notification: Not ECN-Capable Transport (0)"<<endl;
                output<<"Explicit Congestion Notification: Not ECN-Capable Transport (0)"<<endl;
            }
            else
            {
//                cout<<"Explicit Congestion Notification: Yes "<<hex<<byte<<endl;
                output<<"Explicit Congestion Notification: Yes "<<hex<<byte<<endl;
            }

            file.read((char*)buf, 2);
            int x=static_cast<int>(buf[0]);
            int y=static_cast<int>(buf[1]);
            x=x*256+y;
//            cout<<"Total lenght: "<<dec<<x<<endl;
            output<<"Total lenght: "<<dec<<x<<endl;

            file.read((char*)buf, 2);
            x=static_cast<int>(buf[0]);
            y=static_cast<int>(buf[1]);
            temp=x*256+y;
//            cout<<"Identification: "<<dec<<temp<<endl;
            output<<"Identification: "<<dec<<temp<<endl;

            file.read((char*)buf, 2);
            x=static_cast<int>(buf[0]);
            y=static_cast<int>(buf[1]);
            temp=x*256+y;
            byte=temp&32768;
//            cout<<"Flags:"<<endl;
            output<<"Flags:"<<endl;
            if (byte==0)
            {
//                cout<<"  Reserved: false"<<endl;
                output<<"  Reserved: false"<<endl;
            }
            else
            {
//                cout<<"  Reserved: true"<<endl;
                output<<"  Reserved: true"<<endl;
            }
            byte=temp&16384;
            if (byte==0)
            {
//                cout<<"  Do not fragment: false"<<endl;
                output<<"  Do not fragment: false"<<endl;
            }
            else
            {
//                cout<<"  Do not fragment: true"<<endl;
                output<<"  Do not fragment: true"<<endl;
            }
            byte=temp&8192;
            if (byte==0)
            {
//                cout<<"  More fragments: false"<<endl;
                output<<"  More fragments: false"<<endl;
            }
            else
            {
//                cout<<"  More fragments: true"<<endl;
                output<<"  More fragments: true"<<endl;
            }
            byte=temp&8191;
//            cout<<"Fragment Offset: "<<byte*8<<endl;
            output<<"Fragment Offset: "<<byte*8<<endl;

            file.read((char*)buf, 2);
            temp=static_cast<int>(buf[0]);
//            cout<<"TTL: "<<temp<<endl;
            output<<"TTL: "<<temp<<endl;
            temp=static_cast<int>(buf[1]);
//            cout<<"Protocol: ";
            output<<"Protocol: ";
            protocol(temp);


            file.read((char*)buf, 2);
            x=static_cast<int>(buf[0]);
            y=static_cast<int>(buf[1]);
            temp=x*256+y;
//            cout<<"Header checksum: 0x"<<hex<<temp<<endl;
            output<<"Header checksum: 0x"<<hex<<temp<<endl;

            file.read((char*)buf, 4);
            temp=static_cast<int>(buf[0]);
//            cout<<"Source: "<<dec<<temp<<".";
            output<<dec<<"Source: "<<temp<<".";
            temp=static_cast<int>(buf[1]);
//            cout<<dec<<temp<<".";
            output<<dec<<temp<<".";
            temp=static_cast<int>(buf[2]);
//            cout<<dec<<temp<<".";
            output<<dec<<temp<<".";
            temp=static_cast<int>(buf[3]);
//            cout<<dec<<temp<<endl;
            output<<dec<<temp<<endl;

            file.read((char*)buf, 4);
            temp=static_cast<int>(buf[0]);
//            cout<<"Destination: "<<dec<<temp<<".";
            output<<"Destination: "<<dec<<temp<<".";
            temp=static_cast<int>(buf[1]);
//            cout<<dec<<temp<<".";
            output<<dec<<temp<<".";
            temp=static_cast<int>(buf[2]);
//            cout<<dec<<temp<<".";
            output<<dec<<temp<<".";
            temp=static_cast<int>(buf[3]);
//            cout<<dec<<tremp<<endl;
            output<<dec<<temp<<endl<<endl;
//            break;
        }
        else
        {
            file.seekg(-2, ios::cur);
            file.read((char*)buf, 3);
        }
    }
    cout<<endl<<"Work is over"<<endl
       <<"You can find results in file out.txt";
    output.close();
    file.close();
    delete[] buf;
    delete temp_ch;
    return 0;
}

void showInBit(int num)
{
    QString byte;
    cout<<"function"<<endl;
    if (num>0)
        if(num<256)
            for (int i=7; i>=0; i--)
            {
                int temp=(num>>i)&1;
                byte.append(QString::number(temp));
                cout<<temp;
            }
        else
            if (num<65536)
                for (int i=15; i>=0; i--)
                {
                    int temp=(num>>i)&1;
                    byte.append(QString::number(temp));
                    cout<<temp;
                }
            else cout<<"Wrong number...";
    else
        cout<<"Wrong number...";

    cout<<endl<<"byte: "<<byte.toStdString()<<endl;
}
void protocol (int num)
{
    switch (num)
    {
    case 1:
//        cout<<"ICMP"<<endl;
        output<<"ICMP"<<endl;
        break;
    case 2:
//        cout<<"IGMP"<<endl;
        output<<"IGMP"<<endl;
        break;
    case 3:
//        cout<<"IPv4"<<endl;
        output<<"IPv4"<<endl;
        break;
    case 4:
//        cout<<"IGMP"<<endl;
        output<<"IGMP"<<endl;
        break;
    case 5:
//        cout<<"ST"<<endl;
        output<<"ST"<<endl;
        break;
    case 6:
//        cout<<"TCP"<<endl;
        output<<"TCP"<<endl;
        break;
    case 7:
//        cout<<"CBT"<<endl;
        output<<"CBT"<<endl;
        break;
    case 9:
//        cout<<"IGP"<<endl;
        output<<"IGP"<<endl;
        break;
    case 10:
//        cout<<"BBN-RCC-MON"<<endl;
        output<<"BBN-RCC-MON"<<endl;
        break;
    case 11:
//        cout<<"NVP-II"<<endl;
        output<<"NVP-II"<<endl;
        break;
    case 12:
//        cout<<"PUP"<<endl;
        output<<"PUP"<<endl;
        break;
    case 13:
//        cout<<"ARGUS"<<endl;
        output<<"ARGUS"<<endl;
        break;
    case 14:
//        cout<<"EMCON"<<endl;
        output<<"EMCON"<<endl;
        break;
    case 15:
//        cout<<"XNET"<<endl;
        output<<"XNET"<<endl;
        break;
    case 16:
//        cout<<"CHAOS"<<endl;
        output<<"CHAOS"<<endl;
        break;
    case 17:
//        cout<<"UDP"<<endl;
        output<<"UDP"<<endl;
        break;
    case 18:
//        cout<<"MUX"<<endl;
        output<<"MUX"<<endl;
        break;
    case 19:
//        cout<<"DCN-MEAS"<<endl;
        output<<"DCN-MEAS"<<endl;
        break;
    case 20:
//        cout<<"HMP"<<endl;
        output<<"HMP"<<endl;
        break;
    case 21:
//        cout<<"PRM"<<endl;
        output<<"PRM"<<endl;
        break;
    case 27:
//        cout<<"RDP"<<endl;
        output<<"RDP"<<endl;
        break;
    case 33:
//        cout<<"DCCP"<<endl;
        output<<"DCCP"<<endl;
        break;
    case 54:
//        cout<<"NARP"<<endl;
        output<<"NARP"<<endl;
        break;
    case 121:
//        cout<<"SMP"<<endl;
        output<<"SMP"<<endl;
        break;
    default:
//        cout<<"It is too lazy to learn them all"<<endl;
        output<<"It is too lazy to learn them all"<<endl;
    }

}
bool check (unsigned char *buf)
{
    int x=static_cast<int>(buf[2]);
    x=x>>4;
    QString temp;
    int arr[3];
    for (int i=0; i<3; i++)
        arr[i]=static_cast<int>(buf[i]);
    for (int i=0; i<2; i++)
    {
        if (arr[i]<10)
        {
            if (arr[i]==0)
                temp.append("00");
            else
            {
                temp.append('0');
                temp.append(QString::number(arr[i], 16));
            }
        }
        else
            temp.append(QString::number(arr[i], 16));
    }
    temp.append(QString::number(x, 16));
//    cout<<endl<<endl<<temp.toStdString();
            if (temp=="08004")
//    if (temp=="32452")
    {
//        cout<<endl<<"true";
        return true;
    }
    else
    {
//        cout<<endl<<"false";
        return false;
    }
}







