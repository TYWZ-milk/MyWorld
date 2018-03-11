if ( ! Detector.webgl ) Detector.addGetWebGLMessage();
//detector是一个探测器，引用了detector.js，用来探测webgl的支持情况

var container;
var camera, scene, renderer;
var plane, cube;
var mouse, raycaster, isShiftDown = false;

var rollOverMesh, rollOverMaterial,rollOverGeo;
var cubeGeo, cubeMaterial;

var objects = [];

init();
render();//渲染



function init(){

    container = document.createElement( 'div' );//使用createElement创建一个div，就是整个页面
    document.body.appendChild( container );//添加子节点

    var info = document.createElement( 'div' );//在大的div中创建第一个div，表示head部分，名字为info
    info.style.position = 'absolute';
    info.style.top = '10px';
    info.style.width = '100%';
    info.style.textAlign = 'center';
    info.innerHTML = '计算机图形学作业：简单模拟我的世界<br><strong>shift + click</strong>：移除图形<br>' +
        '<button class="btn1" onclick="method1()">正方体</button><button class="btn2" onclick="method2()">球体</button>' +
        '<button class="btn3" onclick="method3()">长方体</button><button class="btn4" onclick="method4()">圆柱体</button>' +
        '<br><button class="btn5" onclick="method5()">预览</button>';
    container.appendChild( info );//将创建的info添加到大的div中

    camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 1, 10000 );//设置透视投影的相机
    camera.position.set( 500, 800, 1300 );//设置相机坐标
    camera.lookAt( new THREE.Vector3() );//设置视野的中心坐标

    scene = new THREE.Scene();//设置场景,场景是一个三维空间，用Scene类声明一个对象scene
    // grid，定义画布上的坐标格子
    var size = 500, step = 50;
    var geometry = new THREE.Geometry();//创建一个基本的几何形状
    for ( var i = - size; i <= size; i += step ) {
        geometry.vertices.push( new THREE.Vector3( - size, 0, i ) );
        geometry.vertices.push( new THREE.Vector3(   size, 0, i ) );
        geometry.vertices.push( new THREE.Vector3( i, 0, - size ) );
        geometry.vertices.push( new THREE.Vector3( i, 0,   size ) );
    }
    var material = new THREE.LineBasicMaterial( { color: 0x000000, opacity: 0.2, transparent: true } );
    //创建一个线条材质，线条颜色黑色，透明度0.2
    var line = new THREE.LineSegments( geometry, material );
    scene.add( line );
    raycaster = new THREE.Raycaster();
    mouse = new THREE.Vector2();
    var geometry = new THREE.PlaneBufferGeometry( 1000, 1000 );
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

    renderer = new THREE.WebGLRenderer( { antialias: true } );//生成渲染器对象，锯齿效果为true
    renderer.setClearColor( 0xf0f0f0 );
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight );
    container.appendChild( renderer.domElement );
    document.addEventListener( 'mousemove', onDocumentMouseMove, false );//鼠标移动事件
    document.addEventListener( 'mousedown', onDocumentMouseDown, false );//鼠标点击事件
    document.addEventListener( 'keydown', onDocumentKeyDown, false );//对shift按键的控制
    document.addEventListener( 'keyup', onDocumentKeyUp, false );//对shift按键的控制
    window.addEventListener( 'resize', onWindowResize, false );//窗口改变事件
}



//把创建鼠标跟随几何图形和实体图形都抽象成函数，通过点击事件进行调用
function method1(){
    methodfollow1();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 50, 50, 50 );
    cubeMaterial = new THREE.MeshLambertMaterial( { color: 0xfeb74c, map: new THREE.TextureLoader().load( "textures/square-outline-textured.png" ) } );
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
    cubeMaterial = new THREE.MeshLambertMaterial( { color: 0x4D662D, map: new THREE.TextureLoader().load( "textures/square-outline-textured.png" ) } );
}
function method4(){
    methodfollow4();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.CylinderBufferGeometry( 25,25, 100, 50 ,50);
    cubeMaterial = new THREE.MeshLambertMaterial( { color: 0x4D662D, map: new THREE.TextureLoader().load( "textures/square-outline-textured.png" ) } );
}
function method5(){
    window.open("newwindows.html","_blank","resizable=yes,scrollbars=yes,titlebar=yes,windth=800,height=800");
}

function methodfollow1(){
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
function methodfollow4(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.CylinderGeometry( 25,25 ,100, 50,50 );//创建一个盒状几何对象
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
        } else {
            var voxel = new THREE.Mesh( cubeGeo, cubeMaterial );
            voxel.position.copy( intersect.point ).add( intersect.face.normal );
            voxel.position.divideScalar( 50 ).floor().multiplyScalar( 50 ).addScalar( 25 );
            scene.add( voxel );
            objects.push( voxel );
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

    renderer.render( scene, camera );

}
/**
 * Created by deii66 on 2018/3/11.
 */
