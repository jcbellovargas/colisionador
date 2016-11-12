using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Grafiquera
{
    public partial class Form1 : Form
    {
        bool andando;
        System.IO.FileSystemWatcher file;
        Archivo archivo;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void BtnBuscar_Click(object sender, EventArgs e)
        {

            openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            textBox1.Text = openFileDialog1.FileName;
        }


        private void BtnEmpezar_Click(object sender, EventArgs e)
        {
            if (andando)
            {
                andando = false;
                file.Dispose();
                archivo.Dispose();
                BtnEmpezar.Text = "Empezaar";

            }
            else
            {
                chart1.Series[0].Points.Clear();
                chart1.Series[1].Points.Clear();
                if (!System.IO.File.Exists(textBox1.Text)) throw new Exception("El archivo no existe");
                andando = true;
                BtnEmpezar.Text = "Detener";
                Empezar();
            }
        }

        private void Empezar()
        {

            archivo = new Archivo(textBox1.Text);
            file = new System.IO.FileSystemWatcher(Path.GetDirectoryName(textBox1.Text),Path.GetFileName(textBox1.Text));
            file.EnableRaisingEvents = true;
            file.SynchronizingObject = this;
            file.Changed += new System.IO.FileSystemEventHandler(this.ArchivoActualizado);
            InterpretarTexto(archivo.ObtenerHastaFinal());
        }



        private void InterpretarTexto(string texto)
        { 
            string[] partes = texto.Split(new Char[] {';'});

            for (int i = 0; i < partes.Length; i++)
            {
                if (partes[i] == "") continue;
                string[] datos = partes[i].Split(new Char[] {','});
                AgregarAlGrafico(datos[0],datos[1]);
            }
        }

        private void AgregarAlGrafico(string dato1,string dato2)
        {
            chart1.Series[0].Points.AddY(dato1);//FPS
            chart1.Series[1].Points.AddY(dato2);//CantBolas
        }


        private void ArchivoActualizado(object sender, System.IO.FileSystemEventArgs e)
        {
            InterpretarTexto(archivo.ObtenerHastaFinal());
        }

        private void fileSystemWatcher1_Changed(object sender, System.IO.FileSystemEventArgs e)
        {

        }



    }

    public class Archivo : IDisposable
    {

        private System.IO.FileStream _fileStream;
        private System.IO.StreamReader _reader;


        //Start position is from where to start reading first time. consequent read are managed by the Stream reader
        public Archivo(string direccion, long posicion = 0)
        {
            //Open the file as FileStream
            _fileStream = new FileStream(direccion, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            _reader = new StreamReader(_fileStream);
            //Set the starting position
            _fileStream.Position = posicion;
        }


        //Get the current offset. You can save this when the application exits and on next reload
        //set startPosition to value returned by this method to start reading from that location
        public long CurrentOffset
        {
            get { return _fileStream.Position; }
        }

        //Returns the lines added after this function was last called
        public string ObtenerHastaFinal()
        {
            return _reader.ReadToEnd();
        }



        public void Dispose()
        {
            _reader.Close();
            _fileStream.Close();
        }
    }
}
