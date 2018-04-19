if ( ! Detector.webgl ) Detector.addGetWebGLMessage();
//detector是一个探测器，引用了detector.js，用来探测webgl的支持情况

var container,voxel;
var camera, scene, renderer;
var plane;
var mouse, raycaster, isShiftDown = false;

var rollOverMesh, rollOverMaterial,rollOverGeo;
var cubeGeo, cubeMaterial;
var orbitControl,rotcontrols;
var objects = [];

init();

function init(){

    container = document.createElement( 'div' );//使用createElement创建一个div，就是整个页面
    document.body.appendChild( container );//添加子节点

    camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 1, 10000 );//设置透视投影的相机
    camera.position.set( 500, 800, 1300 );//设置相机坐标
    camera.lookAt( new THREE.Vector3() );//设置视野的中心坐标

    scene = new THREE.Scene();//设置场景,场景是一个三维空间，用Scene类声明一个对象scene

    raycaster = new THREE.Raycaster();
    mouse = new THREE.Vector2();
    var geometry = new THREE.PlaneBufferGeometry( 5000, 5000 );
    geometry.rotateX( - Math.PI / 2 );
    plane = new THREE.Mesh( geometry, new THREE.MeshBasicMaterial( { visible: false } ) );
    scene.add( plane );
    objects.push( plane );
    // 创建环境光为灰色
    var ambientLight = new THREE.AmbientLight( 0x606060 );
    scene.add( ambientLight );
    //创建平行光为白色
    var directionalLight = new THREE.DirectionalLight( 0xffffff );
    directionalLight.position.set( 1, 0.75, 0.5 ).normalize();
    scene.add( directionalLight );

    preModel();
    scene.add(loadGround());
    loadSky();
    initGui();
    loadScene();

    renderer = new THREE.WebGLRenderer( { antialias: true} );//生成渲染器对象，锯齿效果为true
    renderer.setClearColor( 0xf0f0f0 );
    renderer.setSize( window.innerWidth, window.innerHeight );

    orbitControl = new THREE.OrbitControls( camera, renderer.domElement );

    rotcontrols = new THREE.TransformControls(camera,renderer.domElement);
    rotcontrols.addEventListener( 'change', render );
    rotcontrols.setMode("rotate");
    scene.add(rotcontrols);

    container.appendChild( renderer.domElement );
    document.addEventListener( 'mousemove', onDocumentMouseMove, false );//鼠标移动事件
    document.addEventListener( 'mousedown', onDocumentMouseDown, false );//鼠标点击事件
    document.addEventListener( 'keydown', onDocumentKeyDown, false );//对shift按键的控制
    document.addEventListener( 'keyup', onDocumentKeyUp, false );//对shift按键的控制
    window.addEventListener( 'resize', onWindowResize, false );//窗口改变事件
    render();//渲染
}
function loadGround() {
    //add ground
    var texture2 = THREE.ImageUtils.loadTexture("textures/blocks/grass.png");
    texture2.wrapS = THREE.RepeatWrapping;
    texture2.wrapT = THREE.RepeatWrapping;
    texture2.repeat.set(50,50);
    var plane = new THREE.PlaneGeometry(5000,5000);
    plane.rotateX(-Math.PI/2);
    return new THREE.Mesh(plane, new THREE.MeshLambertMaterial({
        map: texture2
    }));
}
function loadSky() {
    var path = "textures/skybox/";//设置路径
    var directions  = ["px", "nx", "py", "ny", "pz", "nz"];//获取对象
    var format = ".jpg";//格式
    //创建盒子，并设置盒子的大小为( 5000, 5000, 5000 )
    var skyGeometry = new THREE.BoxGeometry( 5000, 5000, 5000 );
    //设置盒子材质
    var materialArray = [];
    for (var i = 0; i < 6; i++)
        materialArray.push( new THREE.MeshBasicMaterial({
            map: THREE.ImageUtils.loadTexture( path + directions[i] + format ),//将图片纹理贴上
            side: THREE.BackSide/*镜像翻转，如果设置镜像翻转，那么只会看到黑漆漆的一片，因为你身处在盒子的内部，所以一定要设置镜像翻转。*/
        }));
    var skyMaterial = new THREE.MeshFaceMaterial( materialArray );
    var skyBox = new THREE.Mesh( skyGeometry, skyMaterial );//创建一个完整的天空盒，填入几何模型和材质的参数
    scene.add( skyBox );
}
function loadScene(){
    //mountain();
}

function initGui(){
    var cubecontrols = new function (){
        this.brick = function (){
            cubeBuild('brick');
        };
        this.nether_brick = function (){
            cubeBuild('nether_brick');
        };
        this.bookshelf = function (){
            cubeBuild('bookshelf');
        };
        this.normal = function (){
            cubeBuild('normal');
        };
        this.mycelium = function (){
            cubeBuild('mycelium');
        };
        this.obsidian = function (){
            cubeBuild('obsidian');
        };
        this.netherrack = function (){
            cubeBuild('netherrack');
        };
        this.stonewall = function (){
            cubeBuild('stonewall');
        };
        this.mossywall = function (){
            cubeBuild('mossywall');
        };
        this.endstone = function (){
            cubeBuild('endstone');
        };
        this.gravel = function (){
            cubeBuild('gravel');
        };
        this.dessert = function (){
            cubeBuild('dessert');
        };
        this.sand_stone = function (){
            cubeBuild('sand_stone');
        };
        this.granite = function (){
            cubeBuild('granite');
        };
        this.dirt = function (){
            cubeBuild('dirt');
        };
        this.ice = function (){
            cubeBuild('ice');
        };
        this.hay = function (){
            cubeBuild('hay');
        };
        this.hardened_clay = function (){
            cubeBuild('hardened_clay');
        };

    };
    var colorcubecontrols = new function (){
        this.hardened_clay_stained_black = function (){
            cubeBuild('hardened_clay_stained_black');
        };
        this.hardened_clay_stained_blue = function (){
            cubeBuild('hardened_clay_stained_blue');
        };
        this.hardened_clay_stained_brown = function (){
            cubeBuild('hardened_clay_stained_brown');
        };
        this.hardened_clay_stained_cyan = function (){
            cubeBuild('hardened_clay_stained_cyan');
        };
        this.hardened_clay_stained_gray = function (){
            cubeBuild('hardened_clay_stained_gray');
        };
        this.hardened_clay_stained_green = function (){
            cubeBuild('hardened_clay_stained_green');
        };
        this.hardened_clay_stained_light_blue = function (){
            cubeBuild('hardened_clay_stained_light_blue');
        };
        this.hardened_clay_stained_lime = function (){
            cubeBuild('hardened_clay_stained_lime');
        };
        this.hardened_clay_stained_orange = function (){
            cubeBuild('hardened_clay_stained_orange');
        };
        this.hardened_clay_stained_pink = function (){
            cubeBuild('hardened_clay_stained_pink');
        };
        this.hardened_clay_stained_purple = function (){
            cubeBuild('hardened_clay_stained_purple');
        };
        this.hardened_clay_stained_white = function (){
            cubeBuild('hardened_clay_stained_white');
        };
        this.hardened_clay_stained_yellow = function (){
            cubeBuild('hardened_clay_stained_yellow');
        };
        this.hardened_clay_stained_silver = function (){
            cubeBuild('hardened_clay_stained_silver');
        };
        this.hardened_clay_stained_red = function (){
            cubeBuild('hardened_clay_stained_red');
        };
    };
    var planecontrols = new function (){
        this.cobblestone = function (){
            planeBuild('cobblestone');
        };
        this.water = function (){
            planeBuild('water');
        };
        this.woodfloor = function (){
            planeBuild('woodfloor');
        };
        this.grass = function (){
            planeBuild('grass');
        };
        this.farmland_dry = function (){
            planeBuild('farmland_dry');
        };
        this.farmland_wet = function (){
            planeBuild('farmland_wet');
        };
        this.red_sand = function (){
            planeBuild('red_sand');
        };
        this.sand = function (){
            planeBuild('sand');
        };
        this.snow = function (){
            planeBuild('snow');
        };
        this.clay = function (){
            planeBuild('clay');
        };
    };
    var modelcontrols = new function (){
        this.tree1 = function (){
            loadModel('tree1')
        };
        this.tree2 = function (){
            loadModel('tree2')
        };
        this.tree3 = function (){
            loadModel('tree3')
        };
        this.tree4 = function (){
            loadModel('tree4')
        };
        this.cake = function (){
            cylinderBuild('cake')
        };
    };
    var upplanecontrols = new function (){
        this.daywindow = function (){
            upplaneBuild('daywindow')
        };
        this.irondoor = function (){
            upplaneBuild('irondoor')
        };
    };
    var scenecontrols = new function (){
        this.direction = function (){
            direction()
        };
        this.delete = function (){
            for(var i=0 ; i <objects.length;i++){
                if(objects[i].geometry.type != "PlaneBufferGeometry")
                    scene.remove(objects[i]);
            }
        };
    };

    var sceneGui = new dat.GUI();
    sceneGui.add(scenecontrols, "direction").name("改变物体方向");
    sceneGui.add(scenecontrols, "delete").name("清空画面");

    var upplaneGui = new dat.GUI();
    upplaneGui.add(upplanecontrols, "daywindow").name("窗户");
    upplaneGui.add(upplanecontrols, "irondoor").name("门");

    var modelGui = new dat.GUI();
    modelGui.add(modelcontrols,"cake").name("蛋糕");
    modelGui.add(modelcontrols,"tree1").name("树1");
    modelGui.add(modelcontrols,"tree2").name("树2");
    modelGui.add(modelcontrols,"tree3").name("树3");
    modelGui.add(modelcontrols,"tree4").name("树4");

    var planeGui = new dat.GUI();
    planeGui.add(planecontrols, 'cobblestone').name("石面");
    planeGui.add(planecontrols, 'water').name("水");
    planeGui.add(planecontrols, 'woodfloor').name("木地板");
    planeGui.add(planecontrols, 'grass').name("草地");
    planeGui.add(planecontrols, 'farmland_dry').name("耕地");
    planeGui.add(planecontrols, 'farmland_wet').name("黑土");
    planeGui.add(planecontrols, 'red_sand').name("红沙");
    planeGui.add(planecontrols, 'sand').name("沙地");
    planeGui.add(planecontrols, 'snow').name("雪地");
    planeGui.add(planecontrols, 'clay').name("黏土");


    var colorcubeGui = new dat.GUI();
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_black').name("岩石(黑色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_blue').name("岩石(蓝色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_brown').name("岩石(棕色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_cyan').name("岩石(蓝绿色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_gray').name("岩石(灰色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_green').name("岩石(绿色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_light_blue').name("岩石(淡蓝色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_lime').name("岩石(亮绿色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_orange').name("岩石(橘色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_pink').name("岩石(粉色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_purple').name("岩石(紫色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_red').name("岩石(红色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_white').name("岩石(白色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_yellow').name("岩石(黄色)");
    colorcubeGui.add(colorcubecontrols, 'hardened_clay_stained_silver').name("岩石(银色)");

    var cubeGui = new dat.GUI();
    cubeGui.add(cubecontrols,'brick').name("砖墙");
    cubeGui.add(cubecontrols,'nether_brick').name("旧砖墙");
    cubeGui.add(cubecontrols,'bookshelf').name("书架");
    cubeGui.add(cubecontrols,'normal').name("岩石(有植被)");
    cubeGui.add(cubecontrols,'mycelium').name("岩石(真菌覆盖)");
    cubeGui.add(cubecontrols,'obsidian').name("黑曜石");
    cubeGui.add(cubecontrols,'netherrack').name("地狱石");
    cubeGui.add(cubecontrols,'stonewall').name("石墙");
    cubeGui.add(cubecontrols,'mossywall').name("苔藓墙");
    cubeGui.add(cubecontrols,'endstone').name("白石");
    cubeGui.add(cubecontrols,'gravel').name("砾石");
    cubeGui.add(cubecontrols,'dessert').name("黄石");
    cubeGui.add(cubecontrols,'sand_stone').name("沙石");
    cubeGui.add(cubecontrols,'granite').name("花岗岩");
    cubeGui.add(cubecontrols,'dirt').name("岩层");
    cubeGui.add(cubecontrols,'ice').name("冰块");
    cubeGui.add(cubecontrols,'hay').name("干草堆");
    cubeGui.add(cubecontrols,'hardened_clay').name("硬化黏土");

}

function onWindowResize() {

    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    renderer.setSize( window.innerWidth, window.innerHeight );

}

function onDocumentMouseMove( event ) {
    event.preventDefault();//取消事件的默认动作
    mouse.set( ( event.clientX / window.innerWidth ) * 2 - 1, - ( event.clientY / window.innerHeight ) * 2 + 1 );
    raycaster.setFromCamera( mouse, camera );
    var intersects = raycaster.intersectObjects( objects );
    if ( intersects.length > 0 ) {
        var intersect = intersects[ 0 ];
        rollOverMesh.position.copy( intersect.point ).add( intersect.face.normal );
        rollOverMesh.position.divideScalar( 50 ).floor().multiplyScalar( 50 ).addScalar( 25 );
    }
    render();
}
var changeDirection = false;
function direction(){
    changeDirection = true;
}
var selected;
function onDocumentMouseDown( event ) {
    event.preventDefault();
    mouse.set( ( event.clientX / window.innerWidth ) * 2 - 1, - ( event.clientY / window.innerHeight ) * 2 + 1 );
    raycaster.setFromCamera( mouse, camera );
    var intersects = raycaster.intersectObjects( objects );
    if ( intersects.length > 0 ) {
        var intersect = intersects[ 0 ];
        // delete cube
        if ( isShiftDown ) {
            if ( intersect.object != plane ) {
                scene.remove( intersect.object );
                objects.splice( objects.indexOf( intersect.object ), 1 );
            }
            // create cube
        }
        else if(changeDirection) {
            if ( intersect.object != plane ) {
                for (var i = objects.length - 1; i >= 0; i--)
                    if (intersects[0].object == objects[i]) {
                        selected = objects[i];
                        rotcontrols.attach(selected);
                    }
            }
            else{
                rotcontrols.detach(selected);
            }
        }
        else {
            if(cubeGeo.type != "BufferGeometry" ) {
                voxel = new THREE.Mesh(cubeGeo, cubeMaterial);
                voxel.position.copy(intersect.point).add(intersect.face.normal);
                voxel.position.divideScalar(50).floor().multiplyScalar(50).addScalar(25);
            }
            else{
                voxel = new THREE.Mesh(cubeGeo, cubeMaterial);
                voxel.position.copy(intersect.point).add(intersect.face.normal);
                voxel.position.divideScalar(50).floor().multiplyScalar(50);
                voxel.scale.set(50,50,50);
            }
            scene.add(voxel);
            objects.push(voxel);
        }
        render();
    }
}
function onDocumentKeyDown( event ) {
    switch( event.keyCode ) {
        case 16: isShiftDown = true; break;
    }
}
function onDocumentKeyUp( event ) {
    switch ( event.keyCode ) {
        case 16: isShiftDown = false; break;
    }
}
function render() {

    orbitControl.update();
    renderer.clear();
    renderer.render( scene, camera );

}
/**
 * Created by deii66 on 2018/3/11.
 */
