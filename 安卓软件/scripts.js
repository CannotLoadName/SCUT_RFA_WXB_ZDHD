var nxt="data",nnxt=true;
function start()
{
    nxt="start";
}
function stop()
{
    nxt="stop";
}
function reset()
{
    nxt="reset";
}
function chbool(id,tf)
{
    if(tf==1)
    {
        document.getElementById(id).innerHTML='<font style="color:ForestGreen;">是</font>';
    }
    else if(tf==0)
    {
        document.getElementById(id).innerHTML='<font style="color:FireBrick;">否</font>';
    }
    else
    {
        document.getElementById(id).innerHTML='<font style="color:Gray;">null</font>';
    }
}
function chflt(id,tf)
{
    if(tf>=0)
    {
        document.getElementById(id).innerHTML=tf.toFixed(2);
    }
    else
    {
        document.getElementById(id).innerHTML='<font style="color:Gray;">null</font>';
    }
}
function responser(dic)
{
    dic=JSON.parse(dic);
    chbool("wifi",dic.wifi);
    chbool("helec",dic.helec);
    chbool("melec",dic.melec);
    chbool("lelec",dic.lelec);
    chflt("temper",dic.temper);
    chflt("voltage",dic.voltage);
    chbool("pump",dic.pump);
}
var xmlhttp=new XMLHttpRequest();
xmlhttp.onreadystatechange=function()
{
    if(xmlhttp.readyState==4 && xmlhttp.status==200)
    {
        if(nnxt)
        {
            responser(xmlhttp.responseText);
        }
        xmlhttp.open("GET",nxt,true);
        nnxt=nxt=="data";
        nxt="data";
        xmlhttp.send();
    }
};
xmlhttp.open("GET",nxt,true);
xmlhttp.send();
