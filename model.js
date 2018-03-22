/**
 * Created by deii66 on 2018/3/15.
 */
var tree1,tree2,tree3,tree4;
function preModel(){
    var loader = new THREE.OBJLoader();
    loader.load('model/AL06a.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.material.map = THREE.ImageUtils.loadTexture('textures/models/timg.jpg');
                child.geometry.computeBoundingSphere();
            }
        });
        geometry.scale.set(50, 50, 50);

        tree1 = geometry;
    });
    loader.load('model/Blue Spruce.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.material.map = THREE.ImageUtils.loadTexture('textures/models/timg.jpg');
                child.geometry.computeBoundingSphere();
            }
        });
        geometry.scale.set(50, 50, 50);
        tree2 = geometry;
    });
    loader.load('model/BS07a.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.material.map = THREE.ImageUtils.loadTexture('textures/models/timg.jpg');
                child.geometry.computeBoundingSphere();
            }
        });
        geometry.scale.set(50, 50, 50);
        tree3 = geometry;
    });
    loader.load('model/Scotch Pine.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.material.map = THREE.ImageUtils.loadTexture('textures/models/timg.jpg');
                child.geometry.computeBoundingSphere();
            }
        });
        geometry.scale.set(50, 50, 50);
        tree4 = geometry;
    });
}
function loadModel(model){
    changeDirection = false;
    rotcontrols.detach(selected);

    cubeGeo = null;
    cubeMaterial = null;
    if(model == "tree1") {
        modelFollow("tree1");
        voxel = tree1;
    }
    else if(model == "tree2") {
        modelFollow("tree2");
        voxel = tree2;
    }
    else if(model == "tree3") {
        modelFollow("tree3");
        voxel = tree3;
    }
    else if(model == "tree4") {
        modelFollow("tree4");
        voxel = tree4;
    }
}
function modelFollow(model){
    scene.remove(rollOverMesh);
    var loader = new THREE.OBJLoader();
    if(model == "tree1") {
        loader.load('model/AL06a.obj', function (geometry) {
            geometry.traverse(function (child) {
                if (child instanceof THREE.Mesh) {
                    child.material.depthTest = true;
                    child.material = new THREE.MeshBasicMaterial({color: 0xff0000, opacity: 0.5, transparent: true});
                    child.geometry.computeBoundingSphere();
                }
            });
            geometry.scale.set(50, 50, 50);
            rollOverMesh = geometry;
            scene.add(rollOverMesh);
        });
    }
    else if(model == "tree2"){
        loader.load('model/Blue Spruce.obj', function (geometry) {
            geometry.traverse(function (child) {
                if (child instanceof THREE.Mesh) {
                    child.material.depthTest = true;
                    child.material = new THREE.MeshBasicMaterial({color: 0xff0000, opacity: 0.5, transparent: true});
                    child.geometry.computeBoundingSphere();
                }
            });
            geometry.scale.set(50, 50, 50);
            rollOverMesh = geometry;
            scene.add(rollOverMesh);
        });
    }
    else if(model == "tree3"){
        loader.load('model/BS07a.obj', function (geometry) {
            geometry.traverse(function (child) {
                if (child instanceof THREE.Mesh) {
                    child.material.depthTest = true;
                    child.material = new THREE.MeshBasicMaterial({color: 0xff0000, opacity: 0.5, transparent: true});
                    child.geometry.computeBoundingSphere();
                }
            });
            geometry.scale.set(50, 50, 50);
            rollOverMesh = geometry;
            scene.add(rollOverMesh);
        });
    }
    else if(model == "tree4"){
        loader.load('model/Scotch Pine.obj', function (geometry) {
            geometry.traverse(function (child) {
                if (child instanceof THREE.Mesh) {
                    child.material.depthTest = true;
                    child.material = new THREE.MeshBasicMaterial({color: 0xff0000, opacity: 0.5, transparent: true});
                    child.geometry.computeBoundingSphere();
                }
            });
            geometry.scale.set(50, 50, 50);
            rollOverMesh = geometry;
            scene.add(rollOverMesh);
        });
    }
}
//把创建鼠标跟随几何图形和实体图形都抽象成函数，通过点击事件进行调用
function cubeBuild(cube){
    changeDirection = false;
    rotcontrols.detach(selected);
    cubeFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 50, 50, 50 );
    if(cube=="brick")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/brick.png" ) } );
    else if(cube=="bookshelf")
        cubeMaterial = new THREE.MeshLambertMaterial( { map: new THREE.TextureLoader().load( "textures/blocks/bookshelf.png" ) } );
    else if(cube=="stonewall")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/stone-wall.jpg" ) } );
    else if(cube=="mossywall")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/cobblestone_mossy.png" ) } );
    else if(cube=="endstone")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/end_stone.png" ) } );
    else if(cube=="normal") {
        var material1 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/atlas.png') } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/dirt.png') } );
        var material3 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/grass.png') } );
        var materials = [material1, material1, material3, material2,material1,material1];
        cubeMaterial = new THREE.MeshFaceMaterial(materials);
    }
}
function planeBuild(plane){
    changeDirection = false;
    rotcontrols.detach(selected);
    planeFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 50, 10, 50 );
    if(plane=="water")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/water_flow.png" ) } );
    else if(plane=="woodfloor")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/wood-floor.jpg" ) } );
    else if(plane=="clay")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/clay.png" ) } );
    else if(plane=="cobblestone")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/cobblestone.png" ) } );
    else if(plane=="dirt")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/dirt.png" ) } );
    else if(plane=="grass")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/grass.png" ) } );
    for(var i=0; i <cubeGeo.vertices.length;i++){
        cubeGeo.vertices[i].y = -23;
    }

}
function upplaneBuild(upplane){
    changeDirection = false;
    rotcontrols.detach(selected);
    upplaneFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 1, 50, 50 );
    if(upplane=="daywindow")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/daylight_detector_top.png" ) } );
    else if(upplane=="irondoor") {
        var material1 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/door_iron_lower.png') } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/door_iron_upper.png') } );
        var materials = [material2, material1];
        cubeMaterial = new THREE.MeshFaceMaterial(materials);
    }

}
function cylinderBuild(scylinder){
    changeDirection = false;
    cylinderFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.CylinderBufferGeometry( 10,10, 10, 18 ,3);
    if(scylinder=="cake") {
        var material1 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/cake_inner.png') } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/cake_bottom.png') } );
        var material3 = new THREE.MeshPhongMaterial( {
            map: THREE.ImageUtils.loadTexture('textures/blocks/cake_top.png') } );
        var materials = [material1, material3, material2];
        cubeMaterial = new THREE.MeshFaceMaterial(materials);
    }
}
function cubeFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.BoxGeometry( 50, 50, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
function planeFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.BoxGeometry( 50, 10, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    for(var i=0; i <rollOverGeo.vertices.length;i++){
        rollOverGeo.vertices[i].y = -23;
    }
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
function cylinderFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.CylinderBufferGeometry( 10,10, 10, 18 ,3);//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
function upplaneFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.BoxGeometry( 10, 50, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );

    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
