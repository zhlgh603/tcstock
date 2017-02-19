
#include <QString>
#include <QStringList>
#include <QApplication>

typedef struct _tdx_lday
{
    unsigned long date;             //日期
    unsigned long open;             //开盘价，单位：分
    unsigned long high;             //最高价，单位：分
    unsigned long low;              //最低价，单位：分
    unsigned long close;            //收盘价，单位：分
    float         amount;           //交易金额，单位：元
    unsigned long vol;              //成交量，单位：股
    unsigned long reserv;           //保留，有时用来保存上一交易日收盘价
} tdx_lday;

typedef struct _tdx_tnf_header
{
    char unknown[50];
} tdx_tnf_header;

typedef struct _tdx_tnf_m
{
    char dm[23];                    //代码
    char mc[49];                    //名称
    char unknown_1[213];
    char sx[29];                    //缩写
} tdx_tnf_m;

typedef struct _tdx_tnf_ex
{
    char dm[9];                     //代码
    char unknown_1[15];
    char mc[18];                    //名称
    char unknown_2[199];
    char sx[9];                     //缩写
} tdx_tnf_ex;


void print_record(tdx_lday *lday)
{
    printf("[%ld][%ld][%ld][%ld][%ld][%f][%ld][%ld]\n",
           lday->date,
           lday->open,
           lday->high,
           lday->low,
           lday->close,
           lday->amount,
           lday->vol,
           lday->reserv);
    fflush(stdout);
}

void parse_tnf_m()
{
    QFile f("E:/stocks/new_gxzq_v6/T0002/hq_cache/shm.tnf");
    if(!f.open(QIODevice::ReadOnly))
    {
        return;
    }
    int len = sizeof(tdx_tnf_header);
    tdx_tnf_header tnf_header;
    char *p = (char *)&tnf_header;
    memset(p, 0, len);
    f.read(p, len);

    len = sizeof(tdx_tnf_m);
    tdx_tnf_m tnf_item;
    p = (char *)&tnf_item;
    memset(p, 0, len);

    while(len==f.read(p, len))
    {
        printf("[%s][%s][%s]\n",
               tnf_item.dm,
               tnf_item.mc,
               tnf_item.sx
               );
        fflush(stdout);

        memset(p, 0, len);
    }
}

void parse_tnf_ex()
{
    QFile f("E:/stocks/new_gxzq_v6/T0002/hq_cache/szex.tnf");
    if(!f.open(QIODevice::ReadOnly))
    {
        return;
    }
    int len = sizeof(tdx_tnf_header);
    tdx_tnf_header tnf_header;
    char *p = (char *)&tnf_header;
    memset(p, 0, len);
    f.read(p, len);

    len = sizeof(tdx_tnf_ex);
    tdx_tnf_ex tnf_item;
    p = (char *)&tnf_item;
    memset(p, 0, len);

    while(len==f.read(p, len))
    {
        printf("[%s][%s][%s]\n",
               tnf_item.dm,
               tnf_item.mc,
               tnf_item.sx
               );
        fflush(stdout);

        memset(p, 0, len);
    }
}


void parse_lday()
{
    QFile f("E:/stocks/new_gxzq_v6/Vipdoc/sh/lday/sh000018.day");
    if(!f.open(QIODevice::ReadOnly))
    {
        return;
    }
    int len = sizeof(tdx_lday);
    tdx_lday lday;
    char *p = (char *)&lday;
    memset(p, 0, len);
    while(len==f.read(p, len))
    {
        print_record(&lday);
        memset(p, 0, len);
    }

//    parse_tnf_ex();
}

QStringList getStockList(const QString &path)
{
    QStringList result;
    //path="E:/stocks/new_gxzq_v6"
    QString fileName = path + "/T0002/hq_cache/shm.tnf";
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly))
    {
        return result;
    }
    int len = sizeof(tdx_tnf_header);
    tdx_tnf_header tnf_header;
    char *p = (char *)&tnf_header;
    memset(p, 0, len);
    f.read(p, len);

    len = sizeof(tdx_tnf_m);
    tdx_tnf_m tnf_item;
    p = (char *)&tnf_item;
    memset(p, 0, len);

    while(len==f.read(p, len))
    {
        printf("[%s][%s][%s]\n",
               tnf_item.dm,
               tnf_item.mc,
               tnf_item.sx
               );
        fflush(stdout);

        QString stock = QString("%s,%s,%s")
                .arg(tnf_item.dm)
                .arg(tnf_item.mc)
                .arg(tnf_item.sx);
        if(-1==result.indexOf(stock))
        {
            result.append(stock);
        }

        memset(p, 0, len);
    }
}

QStringList getStockHistoryValue(const QString &stockcode)
{
    QStringList result;
    QString fileName = QString("E:/stocks/new_gxzq_v6/Vipdoc/sh/lday/sh%1.day").arg(stockcode);
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly))
    {
        return;
    }
    int len = sizeof(tdx_lday);
    tdx_lday lday;
    char *p = (char *)&lday;
    memset(p, 0, len);
    while(len==f.read(p, len))
    {
//        QString value = QString("[%ld][%ld][%ld][%ld][%ld][%f][%ld][%ld]\n",
//               lday->date,
//               lday->open,
//               lday->high,
//               lday->low,
//               lday->close,
//               lday->amount,
//               lday->vol,
//               lday->reserv);
//        fflush(stdout);
        memset(p, 0, len);
        qApp->processEvents();
    }

    return result;

}
