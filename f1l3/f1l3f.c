#include<emscripten.h>
EM_JS(void,ma,(),{
let W=new WebAssembly.Memory({initial:5});
let wasmbuff=new Uint8ClampedArray(W.buffer,0,128); 
const textEncoder = new TextEncoder();
let string="test test 1234 test test";
let encoded = textEncoder.encode(string);
encoded=new Uint8ClampedArray(encoded);
wasmbuff.set(encoded,0);
let utf8decoder = new TextDecoder();
console.log(utf8decoder.decode(W.buffer));
let options={type: 'idb',webWorkerSupport: false};
let fa=new BroadcastChannel('f1a',options);
let bz=new BroadcastChannel('bez',options);
bz.postMessage({data: 222});
fa.postMessage({data: 222});
let sbtn=document.getElementById('sbtn');
sbtn.addEventListener("click",function(){
// let fileHandler= window.showSaveFilePicker({suggestedName: 'test.txt',types: [{description: 'TEXT',accept: {'text/txt': ['.txt'],},}],});
     var db;
         var request = window.indexedDB.open("F1L3", 1);
         request.onsuccess = function(event) {
            db = request.result;
        
         };
         request.onupgradeneeded = function(event) {
            var db = event.target.result;
            var objectStore = db.createObjectStore("parts", {keyPath: "part"});
         }
         function read() {
            var transaction = db.transaction(["parts"]);
            var objectStore = transaction.objectStore("parts");
            var request = objectStore.get("00");
            request.onsuccess = function(event) {
               if(request.result) {
                  console.log("Output data:"+request.result.data);
               }
            };
         }
  read();
});});
int main(){
ma();
return 1;}
