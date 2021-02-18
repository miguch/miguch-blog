---
date: 2021-2-18
tags: 
  - 技术记录
Author: Miguel Chen
---

# Go 语言实现命令行工具 Selpg

**[仓库地址](https://github.com/Miguel-Chan/selpg-go)**

### 参考

[开发 Linux 命令行实用程序](https://www.ibm.com/developerworks/cn/linux/shell/clutil/index.html)

[spf13/pflag](https://github.com/spf13/pflag)

[spf13/cobra](https://github.com/spf13/cobra)

[C语言代码](https://www.ibm.com/developerworks/cn/linux/shell/clutil/selpg.c)

## 设计

### pflag

Selpg 程序首先要处理的是程序接收到的选项参数，我们引入 [pflag](https://godoc.org/github.com/spf13/pflag)，它是用于替代 go 语言自带的flag，提供了POSIX 风格的选项参数处理。这里介绍一下 pflag 的几种定义参数的方式：

1. 函数名为类型名，定义一个对应类型的选项参数，运行程序后函数返回获取到的参数值的指针；另外还可使用函数名为类型名加 p，作用相同但可以添加一个参数的缩写。函数另外接受的 value 参数是选项的默认值，usage 参数为选项的描述：

   ```go
   func Bool(name string, value bool, usage string) *bool
   func BoolP(name, shorthand string, value bool, usage string) *bool
   func Int(name string, value int, usage string) *int
   func IntP(name, shorthand string, value int, usage string) *int
   ```

2. 函数名为类型名加 Var，此时函数没有返回值，接受的第一个参数为绑定的变量的指针，获取到的参数值将存入该变量。

   ```go
   func BoolVar(p *bool, name string, value bool, usage string)
   func BoolVarP(p *bool, name, shorthand string, value bool, usage string)
   func IntVar(p *int, name string, value int, usage string)
   func IntVarP(p *int, name, shorthand string, value int, usage string)
   ```

程序将接受如下形式的 flag（假设 a 为 int 类型，默认72，b 为 bool 类型，默认 false）：

```
//a == 1
-a1
-a=1
-a 1

//a == 72(未指定则使用默认选项值)

//b == true
-b
-b=true
```

### cobra

cobra 是一个可以用于创建 Go 语言命令行应用的库，由 pflag 的创建者 spf13 创建。

我们先通过下面的命令将 cobra 安装：

```
go get -u github.com/spf13/cobra/cobra
```

然后到我们的项目目录下使用`cobra init`即可创建一个 cobra 项目。

cobra 项目的结构如下：

```
  ▾ appName/
    ▾ cmd/
        add.go
        your.go
        commands.go
        here.go
      main.go
```

其中 cmd 文件夹中定义的是应用的各个子命令。由于Selpg 没有子命令，所以我们在这个项目中只需要一个根命令即可。

在命令的代码文件中我们可以看到如下内容：

```go
var rootCmd = &cobra.Command{
    //应用的介绍
	Use:   "",
	Short: "",
	Long: "",

    //对子命令参数的处理
	Args: func(cmd *cobra.Command, args []string) error {
		
	},

    //子命令运行
	Run: func(cmd *cobra.Command, args []string) {
		
	},
}

//init()函数中，添加 flag 定义和其他相关的配置
func init() {
	
}
```

Cobra 源码中使用了 pflag 来实现子命令对选项参数的处理，所以我们**直接使用 cobra 中的 flag 即可**，用法与 pflag 相同。

Cobra 中的 flag 分为两类：`PersisitentFlags() `对于当前的命令及其所有的子命令都有效; 而 `Flags()` 则仅对当前的命令有效。

Cobra 中还可以使用`MarkFlagRequired`和`MarkPersistentFlagRequired` 函数来[将需要的选项参数标记为强制](https://github.com/spf13/cobra/pull/502)，这使得 selpg 中的`-s` 和`-e` 选项的强制性容易实现。

selpg 可接受的参数如下：

`-s`：打印的页面范围的起始页号码（从1开始计算）

`-e` ：打印的范围的最后一页页码

以上两个是必须指定的选项。

`-f`选项表示程序从输入中会将ASCII 换页字符（十进制数值为 12，用“\f”表示）作为换页的标记；

`-l` 选项后接每页的行数，表示程序将把输入中每个指定行数的区间视为一页（若未指定则默认每72行一页）。

以上两个选项互斥，不可同时指定

`-d` 选项指定打印的输出目的地，若未指定则默认输出至标准输出。指定后程序将会调用`lp` 命令，并将数据通过标准输入传入至程序。

最后一个参数`[in_filename]` 参数用于指定输入文件名，若未指定则程序将从程序的标准输入获得输入数据。

对于这些选项在代码中的定义如下：

```go
	rootCmd.Flags().StringVar(&cfgFile, "config", "", "config file (defalut in $HOME/.cobra.yaml)")
	rootCmd.Flags().IntVarP(&startPage, "start_page", "s", 0,  "The first page to be selected")
	rootCmd.Flags().IntVarP(&endPage, "end_page", "e", 0,  "The last page to be selected")
	rootCmd.Flags().IntVarP(&lineNum, "line_number", "l", 72,  "The number of lines in every page")
	rootCmd.Flags().BoolVarP(&useFormFeed, "form_feed", "f", false, "Use \\f as the seperator of each page")
	rootCmd.Flags().StringVarP(&destination, "destination", "d", "", "Specify printer for output instead of stdout")

	rootCmd.MarkFlagRequired("start_page")
	rootCmd.MarkFlagRequired("end_page")
```



Selpg 完成对输入参数的处理后，创建 selpg 对象进行主要的输入输出工作，具体如下：

### 程序输入

selpg 提供了两种输入方式：第一个非选项的参数为输入的文件名，或未指定文件名时将使用标准输入作为程序输入。

在程序开始读取输入前，根据获得的选项创建一个`bufio.Reader`对象，使用该对象进行读取输入：

```go
	var reader io.Reader
	if sp.inputFile != "" {
		file, err := os.Open(sp.inputFile)
		if err != nil {
			fmt.Fprintf(os.Stderr, "%v: Could not open file: %v, %v\n", os.Args[0], sp.inputFile, err)
			os.Exit(1)
		}
		reader = file
	} else {
		reader = os.Stdin
	}
	bufReader := bufio.NewReader(reader)
```

`bufio.NewReader` 接收一个 io.Reader 作为参数，而`os.Open`的返回值和`os.Stdin`都是`*File`类型，因此可以用于创建一个 `bufio.Reader`，创建后可调用其`ReadByte`和`ReadString`方法进行读取。

### 程序输出

程序分为两种输出方式：若指定了`-d`选项参数，则程序会启动`lp` 命令并将输出内容输入至该子进程的标准输入中，否则使用标准输出进行输出。

 `selpg.GetPage`函数接收一个`io.Writer`作为输出目的。程序通过如下方式决定输出目的地：

```go
	buf := new(bytes.Buffer)
	if sp.destination != "" {
		cmd = exec.Command("lp", fmt.Sprintf("-d%v", sp.destination))
		writer = buf
        cmd.Stdin = buf
	} else {
		writer = os.Stdout
	}
	err := sp.GetPages(writer)
```

### 子进程输出

`lp`命令出现错误（如找不到打印机）时，将会输出信息到其标准错误输出中。

对于这些错误信息，这里使用`io.Pipe`来读取并输出至主进程的 stderr。

```go
	piper, pipew := io.Pipe()
		stderr, _ := cmd.StderrPipe()
		go func() {
			defer pipew.Close()
			io.Copy(pipew, stderr)
		}()
```

将 pipe 获得的输入传入主进程的 stderr：

```go
		cmd.Run()
		io.Copy(os.Stderr, piper)
		cmd.Wait()
```

## 程序测试

1. `selpg/selpg_test.go`文件对`selpg.GetPage`方法的运行进行测试，分别读取以每6行为一页的testl.txt 文件和以\f 为分页的 testf.txt 文件进行测试，测试了正常运行、结束页过大、起始页过大时程序的运行情况。

   ```
   $ go test github.com/Miguel-Chan/selpg-go/selpg
   ok  	github.com/Miguel-Chan/selpg-go/selpg	0.009s
   ```


2. 对于从标准输入进行读取的测试：

   ```
   $ ./selpg-go -s1 -e2 -l6 <testl.txt >stdout 2>stderr
   $ cat stdout
   test1
   test1
   test1
   test1
   test1
   test1
   test2
   test2
   test2
   test2
   test2
   test2
   $ cat stderr
   ./selpg-go: Done
   ```

3. 输入选项不完整时的错误：

   ```
   $ ./selpg-go -s1 testl.txt
   Error: required flag(s) "end_page" not set
   Usage:
     selpg-go [flags]
   
   Flags:
         --config string        config file (defalut in $HOME/.cobra.yaml)
     -d, --destination string   Specify printer for output instead of stdout
     -e, --end_page int         The last page to be selected
     -f, --form_feed            Use \f as the seperator of each page
     -h, --help                 help for selpg-go
     -l, --line_number int      The number of lines in every page (default 72)
     -s, --start_page int       The first page to be selected
   
   required flag(s) "end_page" not set
   ```
