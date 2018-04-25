/**
 * Created by deii66 on 2018/4/17.
 */

function randomGrass(){
    var x = -50, z = -50, y = 0;
    var normalrock = new NormalRock();
    normalrock.init();
    normalrock.instance(x*50+25,y*50+25,z*50+25);
    scene.add(normalrock.mesh);
    objects.push(normalrock.mesh);
    for(var i = 0 ; i <4000 ; i++){
        var mesh = normalrock.mesh.clone();
        var random = Math.floor(Math.random() * 3 + 1);
        x+=random;
        if(x >  48 -y){
            z++;
            if(z > -33 -y){
                x = y+1 - 50;z = y+1 - 50; y++;
            }
            else{
                x = y + random - 50;
            }
        }
        mesh.position.set(x*50+25,y*50+25,z*50+25);
        scene.add(mesh);
        objects.push(mesh);
    }
}
function randomDesert(){
    var x = -50, z = -50, y = 0;
    var geo = new THREE.BoxBufferGeometry(50,50,50);
    var material1 = new THREE.MeshPhongMaterial( {
        map: sand_stoneImg } );
    var material2 = new THREE.MeshPhongMaterial( {
        map: sandstone_bottomImg } );
    var material3 = new THREE.MeshPhongMaterial( {
        map: sandstone_topImg } );
    var material4 = new THREE.MeshPhongMaterial( {
        map: sand_stonenormalImg} );
    var materials = [material4, material4, material3, material2,material1,material4];
    var material = new THREE.MeshFaceMaterial(materials);
    var sandstone = new THREE.Mesh(geo,material);

    //for(var i = 0 ; i <50 ; i++){
        x = Math.floor(Math.random() * 50 -50); z = Math.floor(Math.random() * 50 -50); y = 0;
        var level = 4;
        var templevel = 4;
        for(var j = 0; j<30;j++) {
            var mesh = sandstone.clone();
            x++;
            if (level == 0) {
                z++;
                if (templevel == 0) {
                    level = 1;
                    x = y + 1 - 50;
                    z = y + 1 - 50;
                    y++;
                }
                else {
                    templevel--;
                    level = 4;
                    x -= level;
                }
            }
            mesh.position.set(x * 50 + 25, y * 50 + 25, z * 50 + 25);
            scene.add(mesh);
            objects.push(mesh);
            level -- ;
        //}
    }
    var desertgeo = new THREE.PlaneBufferGeometry( 50,  50 );
    desertgeo.rotateX(-Math.PI/2);
    var desertmaterial = new THREE.MeshLambertMaterial( {  map: red_sandImg } );
    var desertmesh = new THREE.Mesh(desertgeo,desertmaterial);
    x = 50;z=49;
    for(var i=0;i<5050;i++) {
        var clone = desertmesh.clone();
        clone.position.set(x * 50 , 1, z * 50 + 25);
        x--;
        if(x==-51){x=50;z--;}
        scene.add(clone);
        objects.push(clone);
    }
}
function river(){
    var geo = new THREE.PlaneBufferGeometry( 50,  50 );
    geo.rotateX(-Math.PI/2);
    var material = new THREE.MeshLambertMaterial( {  map: waterImg } );
    var mesh = new THREE.Mesh(geo,material);
    var x = -50,z=-20;
    for(var i=0;i<400;i++) {
        var clone = mesh.clone();
        clone.position.set(x * 50 + 25, 3, z * 50 + 25);
        x++;
        if(x==50){x=-50;z++;}
        scene.add(clone);
        objects.push(clone);
    }
    x =40;z=-16;
    for(var i=0;i<400;i++) {
        var clone = mesh.clone();
        clone.position.set(x * 50 + 25, 3, z * 50 + 25);
        x++;
        if(x==44){x=40;z++;}
        scene.add(clone);
        objects.push(clone);
    }
}
function NormalRock(){
    this.mesh = null;
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