// 创建一个存储棋盘状态的数组
var chessdata = [];
// 控制变量
var currentPlayer = 0; // 0 为 "O"，1 为 "X"
// 存储棋子图片的数组
var myname = ["resource/X.png", "resource/O.png"];

// 从 localStorage 加载胜利次数，默认为0
var xwin = parseInt(localStorage.getItem('xwin')) || 0; 
var ywin = parseInt(localStorage.getItem('ywin')) || 0; 

// 玩家信息
var firstname = '';
var lastname = '';

// 初始化函数
function init() {
    var x = document.getElementById("square");
    x.innerHTML = ''; // 清空棋盘内容

    // 生成 3x3 的 div 方块
    for (var i = 0; i < 3; i++) {
        chessdata[i] = [];
        for (var j = 0; j < 3; j++) {
            chessdata[i][j] = 0; // 初始化棋盘状态
            x.innerHTML += `<div onclick="drawfigure(this, ${i}, ${j})"></div>`;
        }
    }

    // 获取玩家信息
    const urlParams = new URLSearchParams(window.location.search);
    firstname = urlParams.get('firstname');
    lastname = urlParams.get('lastname');

    // 显示玩家信息
    updateScores();
}

// 绘制棋子的函数
function drawfigure(obj, x, y) {
    if (chessdata[x][y] !== 0) {
        alert("此处有棋子了！");
        return;
    }

    chessdata[x][y] = currentPlayer + 3; // 3 为 "X"，4 为 "O"
    obj.innerHTML = `<img src="${myname[currentPlayer]}"/>`;
    currentPlayer = 1 - currentPlayer; // 切换玩家
    
    if (calculate(x, y)) 
    {
        return; // 如果有胜利者，则不继续
    }
    
}

// 计算当前落子位置是否满足胜利条件
function calculate(x, y) {
    if (checkWin(x, y)) {
        setTimeout(resetBoard, 2000);
        updateWinCount(currentPlayer);
        alert(`${currentPlayer === 0 ? 'O' : 'X'} win`);
        return true; // 游戏结束
    }
    if (checkFull()) {
        setTimeout(resetBoard, 2000); 
        alert("棋盘已满，游戏结束！");
    }
    return false;
}

// 检查胜利条件
function checkWin(x, y) {
    const sum = chessdata[x].reduce((a, b) => a + b, 0);
    const sumCol = chessdata[0][y] + chessdata[1][y] + chessdata[2][y];
    const sumDiag1 = (x === y) ? (chessdata[0][0] + chessdata[1][1] + chessdata[2][2]) : 0;
    const sumDiag2 = (x + y === 2) ? (chessdata[0][2] + chessdata[1][1] + chessdata[2][0]) : 0;

    return sum === 12 || sumCol === 12 || sumDiag1 === 12 || sumDiag2 === 12 ||
           sum === 9 || sumCol === 9 || sumDiag1 === 9 || sumDiag2 === 9;
}

// 更新胜利次数
function updateWinCount(player) {
    if (player === 0) {
        xwin++;
        localStorage.setItem('xwin', xwin);
    } else {
        ywin++;
        localStorage.setItem('ywin', ywin);
    }
    updateScores();
}

// 检查棋盘是否已满
function checkFull() {
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (chessdata[i][j] === 0) return false;
        }
    }
    return true;
}

// 更新玩家胜利次数显示
function updateScores() { 
    const player1 = `<span class="player">玩家1: ${firstname}</span> <span class="wins">胜利次数: ${xwin}</span>`;
    const player2 = `<span class="player">玩家2: ${lastname}</span> <span class="wins">胜利次数: ${ywin}</span>`;
    document.getElementById('players').innerHTML = `${player1} ; ${player2}`;
}


// 重置棋盘
function resetBoard() {
    chessdata = []; // 清空棋盘状态
    currentPlayer = 0; // 重置当前玩家
    init(); // 重新初始化棋盘
}

// 绑定结算按钮事件
document.getElementById('endGameButton').onclick = function() {
    window.location.href = 'end.html?firstname=' + firstname + '&lastname=' + lastname;
};

// 页面加载时初始化
window.onload = init;
