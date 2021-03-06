/**
 * Created by deii66 on 2018/3/15.
 */
var tree1,tree2,tree3,tree4,branchImg,brickImg,nether_brickImg,obsidianImg,netherrackImg,bookshelfImg,stonewallImg,mossywallImg,endstoneImg,dirtImg;
var dessertImg,gravelImg,hardened_clayImg,iceImg,hay_block_sideImg,hay_block_topImg,mycelium_sideImg,mycelium_topImg,hardened_clay_stained_blackImg;
var hardened_clay_stained_blueImg,hardened_clay_stained_brownImg,hardened_clay_stained_cyanImg,hardened_clay_stained_grayImg,hardened_clay_stained_greenImg;
var hardened_clay_stained_light_blueImg,hardened_clay_stained_limeImg,hardened_clay_stained_orangeImg,hardened_clay_stained_pinkImg,hardened_clay_stained_purpleImg;
var hardened_clay_stained_redImg,hardened_clay_stained_whiteImg,hardened_clay_stained_yellowImg,hardened_clay_stained_silverImg,graniteImg;
var atlasImg,grassImg,sand_stoneImg,sandstone_bottomImg,sandstone_topImg,sand_stonenormalImg,waterImg,red_sandImg,sandImg,snowImg,woodfloorImg;
var clayImg,cobblestoneImg,farmland_dryImg,farmland_wetImg,daywindowImg,door_iron_lowerImg,door_iron_upperImg;
var initRock;
var vertices = new Float32Array( [
    -25.0, -25.0,  25.0,
    25.0, -25.0,  25.0,
    25.0,  25.0,  25.0,

    25.0,  25.0,  25.0,
    -25.0,  25.0,  25.0,
    -25.0, -25.0,  25.0,

    25.0, 25.0, 25.0,
    25.0 , -25.0, 25.0,
    25.0, -25.0, -25.0,

    25.0, -25.0, -25.0,
    25.0 , 25.0, -25.0,
    25.0, 25.0, 25.0,

    -25.0, -25.0,  -25.0,
    -25.0, -25.0,  25.0,
    -25.0,  25.0,  25.0,

    -25.0,  25.0,  25.0,
    -25.0,  25.0,  -25.0,
    -25.0, -25.0,  -25.0,

    25.0, -25.0,  -25.0,
    -25.0, -25.0,  -25.0,
    -25.0,  25.0,  -25.0,

    -25.0,  25.0,  -25.0,
    25.0 , 25.0, -25.0,
    25.0, -25.0,  -25.0,

    25.0,  -25.0,  25.0,
    -25.0,  -25.0,  25.0,
    -25.0, -25.0,  -25.0,

    -25.0, -25.0,  -25.0,
    25.0,  -25.0,  -25.0,
    25.0,  -25.0,  25.0,

    -25.0,  25.0,  -25.0,
    -25.0,  25.0,  25.0,
    25.0, 25.0,  25.0,

    25.0, 25.0,  25.0,
    25.0,  25.0,  -25.0,
    -25.0,  25.0,  -25.0

] );
function preModel(){
    brickImg = new THREE.TextureLoader().load( "textures/blocks/brick.png" );
    branchImg = new THREE.TextureLoader().load( "textures/models/timg.jpg" );
    nether_brickImg = new THREE.TextureLoader().load( "textures/blocks/nether_brick.png" );
    obsidianImg = new THREE.TextureLoader().load( "textures/blocks/obsidian.png" );
    netherrackImg= new THREE.TextureLoader().load( "textures/blocks/netherrack.png" );
    bookshelfImg = new THREE.TextureLoader().load( "textures/blocks/bookshelf.png" );
    stonewallImg = new THREE.TextureLoader().load( "textures/blocks/stone-wall.jpg" );
    mossywallImg = new THREE.TextureLoader().load( "textures/blocks/cobblestone_mossy.png" );
    endstoneImg = new THREE.TextureLoader().load( "textures/blocks/end_stone.png" );
    dirtImg = new THREE.TextureLoader().load( "textures/blocks/dirt.png" );
    dessertImg = new THREE.TextureLoader().load( "textures/blocks/glowstone.png" );
    gravelImg = new THREE.TextureLoader().load( "textures/blocks/gravel.png" );
    hardened_clayImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay.png" );
    iceImg = new THREE.TextureLoader().load( "textures/blocks/ice.png" );
    hay_block_sideImg = THREE.ImageUtils.loadTexture('textures/blocks/hay_block_side.png');
    hay_block_topImg = THREE.ImageUtils.loadTexture('textures/blocks/hay_block_top.png');
    mycelium_sideImg = THREE.ImageUtils.loadTexture('textures/blocks/mycelium_side.png');
    mycelium_topImg = THREE.ImageUtils.loadTexture('textures/blocks/mycelium_top.png');
    hardened_clay_stained_blackImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_black.png" );
    hardened_clay_stained_blueImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_blue.png" );
    hardened_clay_stained_brownImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_brown.png" );
    hardened_clay_stained_cyanImg =new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_cyan.png" );
    hardened_clay_stained_grayImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_gray.png" );
    hardened_clay_stained_greenImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_green.png" );
    hardened_clay_stained_light_blueImg =new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_light_blue.png" );
    hardened_clay_stained_limeImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_lime.png" );
    hardened_clay_stained_orangeImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_orange.png" );
    hardened_clay_stained_pinkImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_pink.png" );
    hardened_clay_stained_purpleImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_purple.png" );
    hardened_clay_stained_redImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_red.png" );
    hardened_clay_stained_whiteImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_white.png" );
    hardened_clay_stained_yellowImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_yellow.png" );
    hardened_clay_stained_silverImg = new THREE.TextureLoader().load( "textures/blocks/hardened_clay_stained_silver.png" );
    graniteImg = new THREE.TextureLoader().load( "textures/blocks/stone_granite.png" );
    atlasImg = new THREE.ImageUtils.loadTexture('textures/blocks/atlas.png');
    grassImg  = new THREE.ImageUtils.loadTexture('textures/blocks/grass.png');
    sand_stoneImg = new THREE.ImageUtils.loadTexture('textures/blocks/sandstone_carved.png');
    sandstone_bottomImg = new THREE.ImageUtils.loadTexture('textures/blocks/sandstone_bottom.png');
    sandstone_topImg = new THREE.ImageUtils.loadTexture('textures/blocks/sandstone_top.png');
    sand_stonenormalImg = new THREE.ImageUtils.loadTexture('textures/blocks/sandstone_normal.png');
    waterImg = new THREE.TextureLoader().load( "textures/blocks/water_still.png");
    red_sandImg = new THREE.TextureLoader().load( "textures/blocks/red_sand.png" );
    sandImg = new THREE.TextureLoader().load( "textures/blocks/sand.png" );
    snowImg = new THREE.TextureLoader().load( "textures/blocks/snow.png" );
    woodfloorImg = new THREE.TextureLoader().load( "textures/blocks/wood-floor.jpg" );
    clayImg = new THREE.TextureLoader().load( "textures/blocks/clay.png" );
    cobblestoneImg =  new THREE.TextureLoader().load( "textures/blocks/cobblestone.png" );
    farmland_dryImg = new THREE.TextureLoader().load( "textures/blocks/farmland_dry.png" );
    farmland_wetImg = new THREE.TextureLoader().load( "textures/blocks/farmland_wet.png" );
    daywindowImg = new THREE.TextureLoader().load( "textures/blocks/daylight_detector_top.png" );
    door_iron_lowerImg = THREE.ImageUtils.loadTexture('textures/blocks/door_iron_lower.png');
    door_iron_upperImg = THREE.ImageUtils.loadTexture('textures/blocks/door_iron_upper.png');

    var material1 = new THREE.MeshPhongMaterial( {
        map: atlasImg } );
    var material2 = new THREE.MeshPhongMaterial( {
        map: dirtImg } );
    var material3 = new THREE.MeshPhongMaterial( {
        map: grassImg } );
    var materials = [material1, material1, material3, material2,material1,material1];
/*    var material =  new THREE.MeshLambertMaterial({
        // wireframe:true,
        side:THREE.DoubleSide,
        map:atlasImg
    });
    var geo= new THREE.BufferGeometry();
    geo.addAttribute( 'position', new THREE.BufferAttribute( vertices, 3 ) );
    geo.computeVertexNormals();
    initRock = new THREE.Mesh(geo,material);
    initRock.position.set(100,100,100);
    scene.add(initRock);*/
    var geo = new THREE.BoxBufferGeometry(50,50,50);
    initRock = new THREE.Mesh(geo,materials);

    var loader = new THREE.OBJLoader();
    loader.load('model/AL06a.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.geometry.computeBoundingSphere();
            }
        });
        tree1 = geometry;
    });
    loader.load('model/Blue Spruce.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.geometry.computeBoundingSphere();
            }
        });
        tree2 = geometry;
    });
    loader.load('model/BS07a.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.geometry.computeBoundingSphere();
            }
        });
        tree3 = geometry;
    });
    loader.load('model/Scotch Pine.obj', function (geometry) {
        geometry.traverse(function (child) {
            if (child instanceof THREE.Mesh) {
                child.material.depthTest = true;
                child.geometry.computeBoundingSphere();
            }
        });
        tree4 = geometry;
    });
}
function readFile(txt1,txt2){
    var loaderTree1 = new THREE.FileLoader();
    var loaderTree2 = new THREE.FileLoader();
//load a text file a output the result to the console
    loaderTree1.load(
        // resource URL
        txt2,

        // Function when resource is loaded
        function ( data ) {
            var layer = [];
            var circle;
            var x="", y="",z="";
            var radius="";
            var temp=0;
            var branchlength="";
            var trunk=[];
            var child="";
            var position="";
            // output the text to the console
            for(var i=0;i<data.length;i++) {
                temp = 0;
                x="";
                y="";
                z="";
                radius="";
                if(data[i]=='L'){
                    var number=data[i+9].toString();
                    if(data[i+10]!='\r') {
                        number += data[i + 10].toString();
                        if (data[i + 11] != '\r') {
                            number += data[i + 11].toString();
                            i+=14;
                        }
                        else{
                            i+=13;
                        }
                    }
                    else{
                        i+=12;
                    }
                    number = parseInt(number);
                }
                if(data[i+5]=='\r'||data[i+4]=='\r'||data[i+3]=='\r') {
                    branchlength='';
                    child='';
                    position='';
                    while (data[i] != ' ') {
                        child += data[i].toString();
                        i++;
                    }
                    i++;
                    while (data[i] != '\r'){
                        position += data[i].toString();
                        i++;
                    }
                    i+=2;
                    while (data[i] != '\r') {
                        branchlength += data[i].toString();
                        i++;
                    }
                    i += 2;
                }
                for(var j=i;data[j]!='\r'&&j<data.length;j++) {
                    if(data[j]!=' ') {
                        if(temp==0){
                            x+=data[j];
                        }
                        if(temp==1){
                            y+=data[j];
                        }
                        if(temp==2){
                            z+=data[j];
                        }
                        if(temp==3){
                            radius+=data[j];
                        }
                    }
                    else{
                        temp++;
                    }
                }
                i = j+1;
                if(branchlength!=0) {
                    circle = {
                        radius: radius * 70,
                        position:position,//
                        child:child,
                        pos: new THREE.Vector3(x * 70, y * 70, z * 70)
                    };
                    trunk.push(circle);
                    branchlength--;
                    if(branchlength==0){
                        layer.push(trunk);
                        number--;
                        if(number == 0){
                            tree1.push(layer);
                            layer = [];
                        }
                        trunk=[];
                    }
                }
            }
        },

        // Function called when download progresses
        function ( xhr ) {
            console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
        },

        // Function called when download errors
        function ( xhr ) {
            console.error( 'An error happened' );
        }
    );

    loaderTree2.load(
        // resource URL
        txt1,

        // Function when resource is loaded
        function ( data ) {
            var layer = [];
            var circle;
            var x="", y="",z="";
            var radius="";
            var temp=0;
            var branchlength="";
            var trunk=[];
            var child="";
            var position="";
            // output the text to the console
            for(var i=0;i<data.length;i++) {
                temp = 0;
                x="";
                y="";
                z="";
                radius="";
                if(data[i]=='L'){
                    var number=data[i+9].toString();
                    if(data[i+10]!='\r') {
                        number += data[i + 10].toString();
                        if (data[i + 11] != '\r') {
                            number += data[i + 11].toString();
                            i+=14;
                        }
                        else{
                            i+=13;
                        }
                    }
                    else{
                        i+=12;
                    }
                    number = parseInt(number);
                }
                if(data[i+5]=='\r'||data[i+4]=='\r'||data[i+3]=='\r') {
                    branchlength='';
                    child='';
                    position='';
                    while (data[i] != ' ') {
                        child += data[i].toString();
                        i++;
                    }
                    i++;
                    while (data[i] != '\r'){
                        position += data[i].toString();
                        i++;
                    }
                    i+=2;
                    while (data[i] != '\r') {
                        branchlength += data[i].toString();
                        i++;
                    }
                    i += 2;
                }
                for(var j=i;data[j]!='\r'&&j<data.length;j++) {
                    if(data[j]!=' ') {
                        if(temp==0){
                            x+=data[j];
                        }
                        if(temp==1){
                            y+=data[j];
                        }
                        if(temp==2){
                            z+=data[j];
                        }
                        if(temp==3){
                            radius+=data[j];
                        }
                    }
                    else{
                        temp++;
                    }
                }
                i = j+1;
                if(branchlength!=0) {
                    circle = {
                        radius: radius * 70,
                        position:position,//
                        child:child,
                        pos: new THREE.Vector3(x * 70, y * 70, z * 70)
                    };
                    trunk.push(circle);
                    branchlength--;
                    if(branchlength==0){
                        layer.push(trunk);
                        number--;
                        if(number == 0){
                            tree2.push(layer);
                            layer = [];
                        }
                        trunk=[];
                    }
                }
            }
        },

        // Function called when download progresses
        function ( xhr ) {
            console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
        },

        // Function called when download errors
        function ( xhr ) {
            console.error( 'An error happened' );
        }
    );
}
//把创建鼠标跟随几何图形和实体图形都抽象成函数，通过点击事件进行调用
function cubeBuild(cube){
    changeDirection = false;
    rotcontrols.detach(selected);
    cubeFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxBufferGeometry( 50, 50, 50 );
    if(cube=="brick")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: brickImg } );
    if(cube=="nether_brick")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: nether_brickImg } );
    if(cube=="obsidian")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: obsidianImg } );
    if(cube=="netherrack")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: netherrackImg } );
    else if(cube=="bookshelf")
        cubeMaterial = new THREE.MeshLambertMaterial( { map: bookshelfImg } );
    else if(cube=="stonewall")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: stonewallImg } );
    else if(cube=="mossywall")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: mossywallImg } );
    else if(cube=="endstone")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: endstoneImg } );
    else if(cube=="dirt")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: dirtImg } );
    else if(cube=="dessert")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: dessertImg } );
    else if(cube=="gravel")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: gravelImg } );
    else if(cube=="hardened_clay")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clayImg } );
    else if(cube=="ice")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: iceImg } );
    else if(cube=="hay"){
        var material1 = new THREE.MeshPhongMaterial( {
            map: hay_block_sideImg } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: hay_block_topImg } );
        var materials = [material1, material1, material2, material2,material1,material1];
        cubeMaterial = new THREE.MeshFaceMaterial(materials);
    }
    else if(cube=="mycelium"){
        var material1 = new THREE.MeshPhongMaterial( {
            map: mycelium_sideImg } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: mycelium_topImg } );
        var materials = [material1, material1, material2, material2,material1,material1];
        cubeMaterial = new THREE.MeshFaceMaterial(materials);
    }
    else if(cube=="hardened_clay_stained_black")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_blackImg } );
    else if(cube=="hardened_clay_stained_blue")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_blueImg } );
    else if(cube=="hardened_clay_stained_brown")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_brownImg } );
    else if(cube=="hardened_clay_stained_cyan")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_cyanImg } );
    else if(cube=="hardened_clay_stained_gray")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_grayImg } );
    else if(cube=="hardened_clay_stained_green")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_greenImg } );
    else if(cube=="hardened_clay_stained_light_blue")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_light_blueImg } );
    else if(cube=="hardened_clay_stained_lime")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_limeImg } );
    else if(cube=="hardened_clay_stained_orange")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_orangeImg } );
    else if(cube=="hardened_clay_stained_pink")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_pinkImg } );
    else if(cube=="hardened_clay_stained_purple")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_purpleImg } );
    else if(cube=="hardened_clay_stained_red")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_redImg } );
    else if(cube=="hardened_clay_stained_white")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_whiteImg } );
    else if(cube=="hardened_clay_stained_yellow")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_yellowImg} );
    else if(cube=="hardened_clay_stained_silver")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: hardened_clay_stained_silverImg } );
    else if(cube=="granite")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: graniteImg } );
    else if(cube=="normal") {
        var material1 = new THREE.MeshPhongMaterial( {
            map: atlasImg } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: dirtImg } );
        var material3 = new THREE.MeshPhongMaterial( {
            map: grassImg } );
        var materials = [material1, material1, material3, material2,material1,material1];
        cubeMaterial = new THREE.MeshFaceMaterial(materials);
    }
    else if(cube=="sand_stone") {
        var material1 = new THREE.MeshPhongMaterial( {
            map: sand_stoneImg } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: sandstone_bottomImg } );
        var material3 = new THREE.MeshPhongMaterial( {
            map: sandstone_topImg } );
        var material4 = new THREE.MeshPhongMaterial( {
            map: sand_stonenormalImg} );
        var materials = [material1, material4, material3, material2,material4,material4];
        cubeMaterial = new THREE.MeshFaceMaterial(materials);
    }
}
function planeBuild(plane){
    changeDirection = false;
    rotcontrols.detach(selected);
    planeFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.PlaneBufferGeometry( 50,  50 );
    cubeGeo.rotateX(-Math.PI/2);
    if(plane=="water")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: waterImg  } );
    else if(plane=="red_sand")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: red_sandImg } );
    else if(plane=="sand")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: sandImg } );
    else if(plane=="snow")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: snowImg } );
    else if(plane=="woodfloor")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: woodfloorImg } );
    else if(plane=="clay")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: clayImg } );
    else if(plane=="cobblestone")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: cobblestoneImg } );
    else if(plane=="grass")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: grassImg } );
    else if(plane=="farmland_dry")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: farmland_dryImg } );
    else if(plane=="farmland_wet")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: farmland_wetImg } );

}
function upplaneBuild(upplane){
    changeDirection = false;
    rotcontrols.detach(selected);
    upplaneFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxBufferGeometry( 1, 50, 50 );
    if(upplane=="daywindow")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: daywindowImg} );
    else if(upplane=="irondoor") {
        var material1 = new THREE.MeshPhongMaterial( {
            map: door_iron_lowerImg } );
        var material2 = new THREE.MeshPhongMaterial( {
            map: door_iron_upperImg } );
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
    rollOverGeo = new THREE.BoxBufferGeometry( 50, 50, 50 );//创建一个盒状几何对象
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
function loadModel(model){
    changeDirection = false;
    rotcontrols.detach(selected);

    cubeGeo = new THREE.BufferGeometry();
    if(model == "tree1") {
        modelFollow("tree1");
        cubeGeo.addAttribute( 'position', new THREE.Float32BufferAttribute( tree1.children[0].geometry.attributes.position.array , 3 ) );
        cubeGeo.computeVertexNormals();
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: branchImg } );
    }
    else if(model == "tree2") {
        modelFollow("tree2");
        cubeGeo.addAttribute( 'position', new THREE.Float32BufferAttribute( tree2.children[0].geometry.attributes.position.array , 3 ) );
        cubeGeo.computeVertexNormals();
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: branchImg } );
    }
    else if(model == "tree3") {
        modelFollow("tree3");
        cubeGeo.addAttribute( 'position', new THREE.Float32BufferAttribute( tree3.children[0].geometry.attributes.position.array , 3 ) );
        cubeGeo.computeVertexNormals();
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: branchImg } );
    }
    else if(model == "tree4") {
        modelFollow("tree4");
        cubeGeo.addAttribute( 'position', new THREE.Float32BufferAttribute( tree4.children[0].geometry.attributes.position.array , 3 ) );
        cubeGeo.computeVertexNormals();
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: branchImg } );
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
