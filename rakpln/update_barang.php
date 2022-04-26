<?php include "koneksi.php"; ?>
<?php include "header.php"; ?>

<h1 class="text-center">Ubah Data Material</h1>
<hr>

<br>

<form enctype="multipart/form-data" method="POST" class="needs-validation" novalidate>
	<div class="container">
		<?php
		$id = $_GET['id'];

		$getBarang = $koneksi->query("SELECT * FROM tb_statistik  WHERE id='$id'") or die($koneksi->error);
		while ($ambil = $getBarang->fetch_assoc()) {
		?>
			<table class="table table-bordered table-hover">
				<tbody>
					<tr>
						<td width="150px">
							<input type="hidden" name="id" value="<?php echo $ambil['id']; ?>">
							Nama Material
						</td>
						<td>
							<input type="text" class="form-control" name="nama_barang" value="<?php echo $ambil['nama_barang']; ?>" placeholder="Masukkan Satuan Material" required>
						</td>
					</tr>
					<tr>
						<td>Jumlah Material</td>
						<td><input type="text" class="form-control" name="jumlah_barang" value="<?php echo $ambil['jumlah_barang']; ?>" placeholder="Masukkan Jumlah Material" required></td>
					</tr>
					<tr>
						<td>Satuan Material</td>
						<td><input type="text" class="form-control" name="satuan_barang" value="<?php echo $ambil['satuan_barang']; ?>" placeholder="Masukkan Satuan Material" required></td>
					</tr>

					<tr>
						<td>Kode Rak Material</td>
						<td>
							<div class="input-group">
								<input type="text" class="form-control mr-5" name="kode_rak" value="<?php echo $ambil['kode_rak']; ?>" placeholder="kode_rak" required>
							</div>
						</td>
					</tr>
				</tbody>
			</table>
		<?php } ?>
	</div>

	<br>

	<p style="text-align: center;">
		<button class="btn btn-primary mr-2" name="update_barang">Ubah</button>
		<a type="button" class="btn btn-danger mr-2" href="index.php">Batal</a>
	</p>

</form>

<style type="text/css">
	.table {
		margin: 0 auto;
		width: auto;
	}
</style>

<?php

if (isset($_POST['update_barang'])) {
	$id = $_POST['id'];
	$nama_barang = $_POST['nama_barang'];
	$jumlah_barang = $_POST['jumlah_barang'];
	$satuan_barang = $_POST['satuan_barang'];
	$kode_rak = $_POST['kode_rak'];
	// $rak_kolom = $_POST['rak_kolom'];
	// $kode_rak = $rak_kolom . $rak_baris;


	if (!empty($nama_barang) || !empty($jumlah_barang) || !empty($satuan_barang) || !empty($rak_baris) || !empty($rak_kolom)) {
		$koneksi->query("UPDATE tb_statistik SET status_update = 'Perbarui Data', nama_barang = '$nama_barang', jumlah_barang = '$jumlah_barang', satuan_barang = '$satuan_barang', kode_rak = '$kode_rak' WHERE id = '$id'");

		echo "<script>alert('Material berhasil diupdate !');</script>";
		echo "<script>location='index.php';</script>";
	} else {
		echo "<script>alert('Mohon lengkapi semua data !');</script>";
	}
}

?>


<?php include "footer.php"; ?>