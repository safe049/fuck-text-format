" fEditor.vim

filetype plugin on

au BufRead,BufNewFile *.fuck set filetype=fuck

" 定义一个命令来解码.fuck 文件
command! DecodeFuck call DecodeFuckFile()

" 定义一个命令来编码.fuck 文件
command! EncodeFuck call EncodeFuckFile()

function! DecodeFuckFile()
    echom "开始解码..."
    let l:binary_text = join(readfile(expand('%')), "\n")
    let l:decoded_text = system('fEditorDecoder "'. l:binary_text. '"')
    echom "解码后的文本: ". l:decoded_text

    " 将解码后的文本拆分为列表，每行一个元素
    let l:decoded_lines = split(l:decoded_text, "\n")

    " 使用 writefile 将新内容写入文件
    call writefile(l:decoded_lines, expand('%'))

    " 重新读取文件内容到缓冲区
    let @a = l:decoded_text
    edit!

    " 刷新缓冲区显示
    redir END
endfunction

function! EncodeFuckFile()
    echom "开始编码..."
    " 获取文件中的所有行并合并为一个字符串
    let l:text = join(getline(1, '$'), "\n")
    " 直接将 l:text 作为参数传递给 fEditorEncoder
    let l:encoded_text = system('fEditorEncoder '. shellescape(l:text))
    echom "编码后的文本: ". l:encoded_text

    if l:encoded_text!= ''
        let l:encoded_lines = split(l:encoded_text, "\n")
        call writefile(l:encoded_lines, expand('%'))
        let @a = l:encoded_text
        edit!

    " 刷新缓冲区显示
        redir END
    else
        echom "编码错误: 无效的文本。"
    endif
endfunction
