using System.Windows.Media.Imaging;
using WpfMath.Parsers;
using WpfMath.Rendering;
using XamlMath;
using XamlMath.Exceptions;

namespace LaTex {
    class Program
    {
        [STAThread]
        static int Main(string[] args)
        {
            if(args.Length == 0)
            {
                return 3;
            }

            string latex = args[0];
            string fileName = args[1];
            int textStyle = 0;
            string font = "Arial";
            if (args.Length > 2){
                textStyle = int.Parse(args[2]);
            }
            if (args.Length > 3)
            {
                font = args[3];
            }

            try
            {
                var parser = WpfTeXFormulaParser.Instance;
                var formula = parser.Parse(latex);
                var environment = WpfTeXEnvironment.Create((TexStyle)textStyle, 100.0, font);
                var bitmapSource = formula.RenderToBitmap(environment, 100);

                var encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(bitmapSource));
                using (var target = new FileStream(fileName, FileMode.Create))
                {
                    encoder.Save(target);

                }
            }
            catch
            {
                return 2;
            }
            return 1;
        }
    }
}