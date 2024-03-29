#include <emscripten.h>
#include <emscripten/html5.h>
#include <indexed_db.hpp>

#define GET_FUNC_NAME_STR(func) #func
#define DATABASE_NAME "F1L3"
#define TABLE1_NAME "table1"
#define TABLE2_NAME "table2"

static indexed_db_instance_c db_instance={.js_object=val::undefined()};

void f1l(float data){
auto transaction=db_instance.transaction({TABLE1_NAME,TABLE2_NAME},TRANSACTION_READWRITE);
auto table1_store=transaction.objectStore(TABLE1_NAME);
val js_object=val::object();
js_object.set("part",std::string("$03"));
js_object.set("data",data);
auto db_request=table1_store.add(js_object);
}

extern "C" {

void f1(float data){
f1l(data);
}

}

EM_JS(void,ma,(),{
window.open("./f1f.1ink");
let opts={type:'idb',webWorkerSupport:false};
let fa=new BroadcastChannel('strt',opts);
let fl=new BroadcastChannel('url',opts);
fl.addEventListener('message',e=>{
document.getElementById("filoc").innerHTML=e.data;
});
fa.addEventListener('message',e=>{
document.getElementById('strt').click();
});
});


int main(){
ma();
auto db_request=indexedDB.open(DATABASE_NAME,1);
db_request.onupgradeneeded(GET_FUNC_NAME_STR(idb_open_onupgradeneeded));
db_request.onsuccess(GET_FUNC_NAME_STR(idb_open_success));
return 0;
}

void idb_open_onupgradeneeded(val event){
db_instance=db_instance.get_result(event);
db_instance.createObjectStore(TABLE1_NAME,"part",false);
db_instance.createObjectStore(TABLE2_NAME);
main();
}

void idb_open_success(val event){
db_instance=db_instance.get_result(event);
auto transaction=db_instance.transaction({TABLE1_NAME,TABLE2_NAME},TRANSACTION_READWRITE);
auto table1_store=transaction.objectStore(TABLE1_NAME);
auto table2_store=transaction.objectStore(TABLE2_NAME);
val js_object=val::object();
// js_object.set("part",std::string("$03"));
// js_object.set("data",std::string("dataDDDDdata"));
// auto db_request=table1_store.add(js_object);
}

EMSCRIPTEN_BINDINGS(){
function(GET_FUNC_NAME_STR(idb_open_onupgradeneeded),&idb_open_onupgradeneeded);
function(GET_FUNC_NAME_STR(idb_open_success),&idb_open_success);
}
