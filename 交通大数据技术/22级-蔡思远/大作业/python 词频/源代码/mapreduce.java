package mr;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class wordcount {
    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        // Job 类是一个单例模式：
        Job job = Job.getInstance(conf);  // job -> yarn 生成job
        //打包为jar去运行
        job.setJarByClass(wordcount.class);

        // 分别指定Mapper 和Reducer 是哪个类
        job.setMapperClass(WordsMapper.class);
        job.setReducerClass(WordsReducer.class);
        // 制定 Mapper 的输出Key 和 Value的类型
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(LongWritable.class);
        // 指定 Reducer的输出Key 和Value 的类型
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);

        // 设置输入的文件
        Path inputPath = new Path(args[0]);
        // 设置输出的路径 ： 注意这个路径一定不要存在
        Path outputPath = new Path(args[1]);
        
        FileInputFormat.setInputPaths(job,inputPath);
        FileOutputFormat.setOutputPath(job,outputPath);


        // 执行 true -> console打印信息，  false-> 不打印
        job.waitForCompletion(true);
    }
}
WordsMapper.java

package mr;


import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

public class WordsMapper extends Mapper<LongWritable,Text,Text,LongWritable> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        String[] strs = value.toString().split(" ");
        for(String s : strs) {
            context.write(new Text(s),new LongWritable(1));
        }
    }
}

WordsMapper.java

package mr;


import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

public class WordsMapper extends Mapper<LongWritable,Text,Text,LongWritable> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        String[] strs = value.toString().split(" ");
        for(String s : strs) {
            context.write(new Text(s),new LongWritable(1));
        }
    }
}
