function getPuzzleById(id) {
    const xhr = new XMLHttpRequest()
    xhr.open('POST', 'https://squaredle.app/api/index.php', true)
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            const responseData = JSON.parse(xhr.response)
            const puzzleData = responseData.data
            if (puzzleData) {
                mainModule.gridModel.fillGrid(puzzleData.puzzle.board)
            } else {
                popups.errorPopup.open()
            }

            popups.sendIdPopup.close()
            popups.sendIdPopup.isLoading = false
        }
    }
    xhr.send(JSON.stringify({
        "args": {
            "game": "squaredle",
            "puzzleKey": id
        },
        "op": "getPuzzleByKey"
    }))
}
