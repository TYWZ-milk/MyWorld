/**
 * Created by deii66 on 2018/4/17.
 */

function mountain(){
    for(var i = 0 ; i <5 ; i++){
        var normalrock = new NormalRock();
        normalrock.init();
        normalrock.instance(i*50+25,i*50+25,i*50+25);
        scene.add(normalrock.mesh);
    }
}
function NormalRock(){
    this.mesh = null;

    this.visible = true;
}
NormalRock.prototype = {
    update:function () {
        this.mesh.visible = this.visible;
    },
    init:function () {

    },
    instance:function (x,y,z) {
        var mesh = initRock.clone();
        mesh.position.set(x,y,z);
        this.mesh = mesh;

    }
};