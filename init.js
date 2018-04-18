if ( ! Detector.webgl ) Detector.addGetWebGLMessage();
//detector是一个探测器，引用了detector.js，用来探测webgl的支持情况

var container,voxel;
var camera, scene, renderer;
var plane, cube;
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
    loadScene();

    renderer = new THREE.WebGLRenderer( { antialias: true} );//生成渲染器对象，锯齿效果为true
    renderer.setClearColor( 0xf0f0f0 );
    renderer.setPixelRatio( window.devicePixelRatio );
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
    mountain();
}

function method2(){
    methodfollow2();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.SphereGeometry( 50, 10, 10 );
    cubeMaterial = new THREE.MeshLambertMaterial( { color: 0x4D662D/*, map: new THREE.TextureLoader().load( "textures/square-outline-textured.png" )*/ } );
}
function method3(){
    methodfollow3();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.CubeGeometry( 50, 100, 50 );
    cubeMaterial = new THREE.MeshLambertMaterial( { color: 0x4D662D/*, map: new THREE.TextureLoader().load( "textures/square-outline-textured.png" )*/ } );
}
function method5(){
    window.open("newwindows.html","_blank","resizable=yes,scrollbars=yes,titlebar=yes,windth=800,height=800");
}

function methodfollow2(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.SphereGeometry( 50, 10, 10 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
function methodfollow3(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.CubeGeometry( 50, 100, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
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
