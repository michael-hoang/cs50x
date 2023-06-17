function spam() {
    let container = document.getElementById('spam-container');

    for (let i = 0; i < 30; i++) {
        let spam = document.createElement('div');
        spam.className = 'spam';
        spam.style.backgroundImage = "url('../img/spam.png')";

        let randomX = Math.random() * (window.innerWidth - 50);
        let randomY = Math.random() * (window.innerHeight - 50);
        spam.style.left = randomX + 'px';
        spam.style.top = randomY + 'px';

        container.appendChild(spam);
    }
}
