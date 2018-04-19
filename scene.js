/**
 * Created by deii66 on 2018/4/17.
 */

function mountain(){
    var x = -50, z = -50, y = 0;
    for(var i = 0 ; i <5725 ; i++){
        var normalrock = new NormalRock();
        normalrock.init();
        normalrock.instance(x*50+25,y*50+25,z*50+25);
        var random = Math.floor(Math.random() * 3 + 1);
        x+=random;
        if(x >  -10 -y){
            z++;
            if(z > -10 -y){
                x = y+1 - 50;z = y+1 - 50; y++;
            }
            else{
                x = y + random - 50;
            }
        }
        scene.add(normalrock.mesh);
        objects.push(normalrock.mesh);
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