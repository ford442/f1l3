document.getElementById("strt").addEventListener('click',function(){
let pth=document.getElementById("filoc").innerHTML;
let ff=new XMLHttpRequest();
ff.open("GET",pth,true);
ff.responseType="arraybuffer";
ff.onload=function(oEvent){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let W=new WebAssembly.Memory({initial:5});
let wasmbuff=new Uint8ClampedArray(W.buffer,0,128); 
const textEncoder=new TextEncoder();
let encoded=textEncoder.encode(phpdat);
encoded=new Uint8ClampedArray(encoded);
wasmbuff.set(encoded,0);
let fill=Module.cwrap('fl',null,['array'])
fill(w.buffer);
}}
ff.send(null);
});
